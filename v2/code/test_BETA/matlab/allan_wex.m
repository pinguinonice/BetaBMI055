function [ad, tau, sigDelta] = allan_wex(daten,freq,strOp,nTau)

% -------------------------------------------------------------------------
% Berechnung der Allan-Abweichung.
%
% Ver./Datum:       0.1 / 06.03.2009
%
% Aufruf: [akzptiert, beta] = hypoMeanUMUV(daten,mue0,alpha)
% - Eingabe : 
%   [daten]   - Messdaten. In format [Messdaten x Sensor]
%   [freq]    - Abtastfreqenz. Muss einen Skalarwert sein. Das Programm 
%               wird das aber nicht ueberpruefen
%   [strOp]   - Options fuer die Auswahl der Tau
%               'durchgaeningig' - tau geht von 1 bis N./9 Messwerte
%               'potenz2' - tau waechst von 1 mit Potenz 2 und tau < N./9
%               'equilog' - tau waechst von 1 an und hat den gleichen
%                           Abstand im LogLog-Diagram. tau < N./9
%   [nTau]    - Anzahl der Tau bei 'equilog'
% 
% - Ausgabe : 
%   [ad]    - Allan-Abweichungen. Im Format [t x Sensor]
%   [t]     - die den Allan-Abweichungen [ad] entsprechende Zeit.
% 
% Bemerkungen: 
%
% Aufgerufene Funktionen():
%
% Literatur/Referenzen:
% [1] Oliver J. Woodman (2007): An introduction to inertial 
% navigation. University of Cambridge. Computer Laboratory
% [2] Naser El-Sheimy et al. (2008): Analysis and Modeling of Inertial
% Sensors Using Allan Variance. IEEE Transactions on Instrumentation and
% Measurement, Vol 57, No.1, Jan. 2008
% 
% Version/Aenderungen:
%   0.1     File generiert 06.03.2009
%   0.2     Implementieren der prozentualen Fehler der Allan-Abweichungen
%
% Wei Xue, INS, Uni. Stuttgart
% -------------------------------------------------------------------------

if nargin < 3
    strOp = 'durchgaengig';
end

if nargin > 2 && ~ischar(strOp)
    error('Option nicht erkannt');
end

[nPunkte,nSensor] = size(daten);    % gesamte Anzahl der Messungen
maxP = floor(nPunkte./9);    % maximale Anzahl pro Bin
dt = 1./freq;                % Abtastinterval

% nTeilung  -  Anzahl der moeglichen Unterteilungen
% binL  -  Binlaenge (Anzahl der Punkte in einem Bin)
switch lower(strOp)
    case 'durchgaengig'
        binL = transpose(1:maxP);
    case 'potenz2'
        nTeilung = floor(log2(maxP));
        binL = transpose(power(2,0:nTeilung));
    case 'equilog'
        nTeilung = nTau - 1;
        maxLog = log10(maxP./freq);
        minLog = log10(1./freq);
        dBinT = (maxLog-minLog)./nTeilung;        
        binT = minLog + (0:nTeilung).*dBinT;
        binL = round(10.^binT.*freq);
        % die Bins mit gleicher Laenge beseitigen
        dummy = binL(2:end);
        tag = dummy - binL(1:end-1) == 0;
        if any(tag)
            warning('Anzahl der Tau wird angepasst')
        end
        dummy = dummy(~tag);
        binL = transpose([binL(1),dummy]);
        clear maxLog minLog dBinT binT dummy; 
    otherwise
        error('Option nicht erkannt')
end
tau = binL ./ freq;
nTau = length(binL);
dummyAD = zeros(nTau,nSensor);
% Prozentualfehler der Allan-Abweichungen [2]

sigDelta = 1./sqrt(2.*(nPunkte./binL - 1))*ones(1,nSensor); 
for i = 1:nTau   
    nBin = floor(nPunkte./binL(i));   % Anzahl der Bins
    % Die Daten die in diese Schleife im Betracht kommen.
    aDaten = daten(1:(nBin*binL(i)),:);    
    aMean = zeros(nBin,nSensor);
    % Mittelwert fuer jedes Bin von jedem Sensor berechnen
    for j = 1:nSensor
        dummy = reshape(aDaten(:,j),[],nBin);
        dummyMean = mean(dummy,1);
        aMean(:,j) = dummyMean';
    end
    aMeanTPlus = aMean(2:end,:);    % a(t)_i+1
    aMeanT = aMean(1:(end-1),:);    % a(t)
    dummy = (aMeanTPlus - aMeanT).^2;
    konstant = 1./(2.*(nBin-1));
    var = konstant.*sum(dummy,1);   % Allan-Varianz
    dev = sqrt(var);                % Allan-Abweichung
    dummyAD(i,:) = dev;           
end
ad = dummyAD;
