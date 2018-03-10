% Simulating an encoder
clear all;
freq = 3000;
period = 1/freq;
t = 0:period/10:8*period;
tLow = 0.4;
tHigh = 0.6;
x = 0.5*(1+sin(2*pi*freq*t)); % keep signal between [0, 1]
pulses = schmidtt_trigger(x, tLow, tHigh);
count = 0;
n = length(pulses);
current_pulse = 0;
previous_pulse = 0;

for i=1:n
  current_pulse = pulses(i);
  if ((current_pulse ~= previous_pulse) && (current_pulse ~= 0))
    count = count +1;
  end
  previous_pulse = current_pulse;
end

figure;
plot(t, x);
hold on;
plot(t, pulses);

radius = 23.17/2;
circumference = 2*pi*radius;
vel = velocity(circumference, freq, count);