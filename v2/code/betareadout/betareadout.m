clear all
clear all 
close all
% Variablen initialisieren und Fenster oeffnen
port=7000; %<--- Hier eigenen Port definiern (Wie in Arduino Skript)
figure
text(0.5,0.5,strcat('Waiting for input on Port:',num2str(port)));
drawnow
dataraw=zeros(1,165,'uint8');
messung=zeros(1000,7,'int32');
% UTP Port defenieren
udpr = dsp.UDPReceiver('LocalIPPort',port);
%Auf Daten von Port warten und holen, wenn vorhanden 
while true
dataraw=zeros(1,165,'uint8');
while size(dataraw,1)<2
dataraw = udpr();
end
%Ladezustand und Signalstaerke entpacken
perc=dataraw(165);
wifi=typecast(uint8(dataraw(end-4:end-1)), 'int32');
%10 Messungen a 16byte =160x1 Vektoer in  10x16 Array umformen
data=reshape(dataraw(1:160),16,10)';
%Bytes wieder zu Werten zusammensetzen
for i=1:10;
time(i) = typecast(uint8(data(i,1:4)), 'int32');
acc(i,1) = typecast(uint8(data(i,5:6 )), 'int16');
acc(i,2) = typecast(uint8(data(i,7:8 )), 'int16');
acc(i,3) = typecast(uint8(data(i,9:10)), 'int16');
gyro(i,1) = typecast(uint8(data(i,11:12)), 'int16');
gyro(i,2) = typecast(uint8(data(i,13:14)), 'int16');
gyro(i,3) = typecast(uint8(data(i,15:16)), 'int16');
end
%Die aeltesten 10 Messungen loeschen und die Neuen 10 hinzufuegen
messung(1:10,:)=[];    
messung(end+1:end+10,:)=[time' acc gyro];
%% Darstellung
%Beschleunigung
subplot(3,1,1)
title('Beschleunigung')
hold on
    p1=plot(messung(:,1),messung(:,2),'r');
    p2=plot(messung(:,1),messung(:,3),'g');
    p3=plot(messung(:,1),messung(:,4),'b');
axis([messung(1,1), messung(end,1), -5000 5000]);
%Drehraten
subplot(3,1,2)
title('Drehraten')
hold on
    p1=plot(messung(:,1),messung(:,5),'r');
    p2=plot(messung(:,1),messung(:,6),'g');
    p3=plot(messung(:,1),messung(:,7),'b');
axis([messung(1,1), messung(end,1), -5000 5000]);
%Wifi und Signalstaerke
subplot(3,1,3)
title('Telemetrie')
hold on
b1=bar([1 2], [2*(wifi+100)  perc]);
xticklabels({'wifi','battery'})
ylabel('%')
%Zeichnen der Plots
drawnow
    delete(p1);
    delete(p2);
    delete(p3);
    delete(b1);
end




