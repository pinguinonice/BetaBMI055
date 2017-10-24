function [f, amp] = myfft(data, tsamp, p)
%% Wrap around function for fft
%   data   
%   tsamp  = Sample time
%   p      = plot (p = 1 -> loglog; p = 1 -> plot)

if (nargin == 2)
    p = 0;
end

Fs = 1/tsamp;           % Sample Frequency
L = length(data);       % Data Length
NFFT = 2^nextpow2(L);   % Next Power of 2 from length of data
Y = fft(data,NFFT)/L;   % Perfrom FFT
f = Fs/2*linspace(0,1,NFFT/2+1);    % Generate frequency vector
amp = 2*abs(Y(1:NFFT/2+1));

% plot single sided amplitute spectrum
if (p==1)
    loglog(f,amp)
    title('Single sided Amplitude Spectrum of data(t)')
    xlabel('Frequency [Hz]')
    ylabel('|Y(f)|')
end

% plot single sided amplitute spectrum
if (p==2)
    plot(f,amp)
    title('Single sided Amplitude Spectrum of data(t)')
    xlabel('Frequency [Hz]')
    ylabel('|Y(f)|')
end
