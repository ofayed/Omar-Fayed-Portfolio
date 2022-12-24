fc = 300; % Cut off frequency
fs = 1000; % Sampling rate
signal
[b,a] = butter(6,fc/(fs/2)); % Butterworth filter of order 6
x = filter(b,a,signal); % Will be the filtered signal