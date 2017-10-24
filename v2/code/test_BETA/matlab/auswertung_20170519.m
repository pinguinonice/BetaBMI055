%%
% Auswertung MISSIE3 Daten, beta Sensoren
% 2017/05/19
%
% ruhe_lage_boden_seite.log
% Einstellungen:
%   imu.setGyrDLPF_CFG(ICM20601_CFG_DLPF_BW_250);
%   imu.setGyrFchoise_b(ICM20601_GCONFIG_FCHOISE_B_DLPF_EN);
%   imu.setFullScaleGyroRange(ICM20601_GYRO_FS_4000);
%   imu.setFullScaleAccelRange(ICM20601_ACC_FS_32);
%   imu.setAccFchoise_b(ICM20601_ACONFIG2_ACC_FCHOISE_B_DLPF_EN);
%   imu.setAccDLPF_CFG(ICM20601_ACONFIG2_ACC_DLPF_CFG_219);
%
% Messfrequenz 500 Hz
%
%%
close all; clc; clear all;

%%
raw = load('../ruhe_lage_boden_seite.log');

%% Sensor ID
ID1 = 48;
ID2 = 136;

%% Index erstellen um Daten zu trennen
IND1 = raw(:,1) == ID1;
IND2 = raw(:,1) == ID2;

data1 = raw(IND1,:);
data2 = raw(IND2,:);

%%
A_SCALE = 32*2/2^16;
G_SCALE = 4000*2/2^16;

%%
h1= figure;
sp1(1) = subplot(221);
hold on
box on
grid on
plot(data1(:,2)/1000,data1(:,3)*A_SCALE,'r')
plot(data1(:,2)/1000,data1(:,4)*A_SCALE,'g')
plot(data1(:,2)/1000,data1(:,5)*A_SCALE,'b')
title(strcat('Sensor ID#',num2str(ID1),32,'ACC'))
ylabel('[g]')
set(gca,'xTicklabel',[])


sp1(2) = subplot(223);
hold on
box on
grid on
plot(data1(:,2)/1000,data1(:,6)*G_SCALE,'r')
plot(data1(:,2)/1000,data1(:,7)*G_SCALE,'g')
plot(data1(:,2)/1000,data1(:,8)*G_SCALE,'b')
linkaxes(sp1,'x')
title(strcat('Sensor ID#',num2str(ID1),32,'GYR'))
xlabel('[s]')
ylabel('[deg/s]')

sp2(1) = subplot(222);
hold on
box on
grid on
plot(data2(:,2)/1000,data2(:,3)*A_SCALE,'r')
plot(data2(:,2)/1000,data2(:,4)*A_SCALE,'g')
plot(data2(:,2)/1000,data2(:,5)*A_SCALE,'b')
title(strcat('Sensor ID#',num2str(ID2),32,'ACC'))
ylabel('[g]')
set(gca,'xTicklabel',[])

sp2(2) = subplot(224);
hold on
box on
grid on
plot(data2(:,2)/1000,data2(:,6)*G_SCALE,'r')
plot(data2(:,2)/1000,data2(:,7)*G_SCALE,'g')
plot(data2(:,2)/1000,data2(:,8)*G_SCALE,'b')
linkaxes(sp2,'x')
title(strcat('Sensor ID#',num2str(ID2),32,'GYR'))
xlabel('[s]')
ylabel('[deg/s]')
% saveas(h1,'rohdaten','png')

%% Rauchuntersuchung von einem Sensor

%% ax ay ...

ax = data1(:,3)*A_SCALE;
ay = data1(:,4)*A_SCALE;
az = data1(:,5)*A_SCALE;

gx = data1(:,6)*G_SCALE;
gy = data1(:,7)*G_SCALE;
gz = data1(:,8)*G_SCALE;
t = data1(:,2)/1000;

%% Standardabweichung
std_acc = [std(ax) std(ay) std(az)];
std_gyr = [std(gx) std(gy) std(gz)];
f = 1/mean(diff(t));

disp('Dauer der Messung [s]:')
disp('t(end)-t(1) [s]')
disp(t(end) - t(1))

disp('Frequenz [Hz]:')
disp(f)

disp('StdAbw Acc [g]:')
disp(std_acc)

disp('StdAbw Gyr [deg/s]:')
disp(std_gyr)

%% Reduzieren des Mittelwerts

ax = ax - mean(ax);
ay = ay - mean(ay);
az = az - mean(az);

gx = gx - mean(gx);
gy = gy - mean(gy);
gz = gz - mean(gz);

%% ADEV ACC
[ad,tau,sig] = allan_wex([ax ay az],f,'potenz2');
h2 = figure;
loglog(tau,ad(:,1),'r.-')
hold on
grid on
box on
loglog(tau,ad(:,2),'g.-')
loglog(tau,ad(:,3),'b.-')
title('Allan-Deviation ICM20601 Acc')
ylabel('ADEV [g]')
xlabel('tau [s]')

%find tau =~ 1
[c,i] = min(abs(tau - 1));
%tau(i)
legend(strcat('ADEV_x(1) = ',32,num2str(ad(i,1)),' [g]'),...
       strcat('ADEV_y(1) = ',32,num2str(ad(i,2)),' [g]'),...
       strcat('ADEV_z(1) = ',32,num2str(ad(i,3)),' [g]'))
% saveas(h2,'acc_allan_deviation','png')
   
%% ADEV GYR
[ad_g,tau_g,sig_g] = allan_wex([gx gy gz],f,'potenz2');
h3 = figure;
loglog(tau_g,ad_g(:,1),'r.-')
hold on
grid on
box on
loglog(tau_g,ad_g(:,2),'g.-')
loglog(tau_g,ad_g(:,3),'b.-')
title('Allan-Deviation ICM20601 GYR')
ylabel('ADEV [deg/s]')
xlabel('tau [s]')

%find tau =~ 1
[c,i] = min(abs(tau_g - 1));
%tau(i)
legend(strcat('ADEV_x(1) = ',32,num2str(ad_g(i,1)),' [deg/s]'),...
       strcat('ADEV_y(1) = ',32,num2str(ad_g(i,2)),' [deg/s]'),...
       strcat('ADEV_z(1) = ',32,num2str(ad_g(i,3)),' [deg/s]'))
% saveas(h3,'gyr_allan_deviation','png')

%% FFT; f = 500 Hz, Filter bei 250 Hz, Filter nicht sichtbar, Todo: höhere Messfrequenz  
break   
%%
figure
[f_ax, amp_ax] = myfft(ax, 1/f, 1);
hold on
grid on
box on

%%
figure
[f_ay, amp_ay] = myfft(ay, 1/f, 1);
hold on
grid on
box on

%%
figure
[f_az, amp_az] = myfft(az, 1/f, 1);
hold on
grid on
box on

%%
figure
[f_gx, amp_gx] = myfft(gx, 1/f, 1);
hold on
grid on
box on

%%
figure
[f_gy, amp_gy] = myfft(gy, 1/f, 1);
hold on
grid on
box on

%%
figure
[f_gz, amp_gz] = myfft(gz, 1/f, 1);
hold on
grid on
box on
