% 读入音频
[y1, sr1]=audioread('1.wav');
[y2, sr2] = audioread('3.wav');
% subplot(2, 1, 1);

% 音频长度 
i = 110364;

% 分成5段
j = 0:1:5;

% 记录数值
k = zeros(1, 6);
k(1,:) = i*j;
k(1, 6) = length(y1);

% 每一段的值
% y_frame = zeros(5, 110364);

% sound(y1, sr1);
% 采样点
N = 2048;
% 分帧加窗
[f1] = v_enframe(y1,hamming(i, 'periodic'), i/2);
sound(f1(3,:), sr1);

% [f2,t2,w2] = v_enframe(y2, hamming(N,'periodic'), N/2);

% 转化为列向量
% f1 = f1';
% f2 = f2';

% 傅里叶变换
Y1_FFT = fft(f1');
% Y2_FFT = fft(f2);
 
m1 = abs(Y1_FFT');
m2 = zeros(8, length(m1));
for i=1:1:8
    m2(i, :) = (m1(i, :)-min(m1(:)))/(max(m1(:))-min(m1(:)));
end
m3 = m2';


% m2 = abs(Y2_FFT');

n = length(m1(1,:));
f = (0:n-1)*(sr1/n);
for i = 1:1:8
    subplot(4,2,i);
    plot(f(1, 1:n/2), m1(i, 1:n/2));
    xlabel('Frequency');
    ylabel('Amplitude');
end



% y0 = fftshift(Y1_FFT);
% f0 = (-n/2:n/2-1)*(sr1/n);
% m0 = abs(y0);
% plot(f0, m0);





%首先，求最大幅值
mag_max=max(m1(1,1:N/2));
% %求最大幅值处对应的频率，即最大特征频率
fre_max=find(m1(1, 1:N/2)==mag_max);
%fre_max=round(fre_max*sr1/N);
% fre_max=round(fre_max*sr1/N);
% i = 1:1:530;
% plot(i, m1(i, :), 'b-', i, m2(i, :), 'y-');


% f1 = (0:length(Y1_FFT)/2-1) * sr1/length(Y1_FFT);
% plot(f1,m(1:length(y)/2));
% 
% % 互功率谱
% res = Y1_FFT .* conj(Y2_FFT);






% t=0:0.0001:0.1; %时间间隔为0.0001，说明采样频率为10000Hz
% x=square(2*pi*1000*t); %产生基频为1000Hz的方波信号
% n=randn(size(t)); %白噪声
% f=x+n; %在信号中加入白噪声
% figure(1);
% subplot(2,1,1);
% plot(f); %画出原始信号的波形图
% ylabel('幅值(V)');
% xlabel('时间(s)');
% title('原始信号');
% y=fft(f,1000); %对原始信号进行离散傅里叶变换，参加DFT采样点的个数为1000
% subplot(2,1,2);
% m=abs(y);
% f1=(0:length(y)/2-1)'*10000/length(y);%计算变换后不同点对应的幅值
% plot(f1,m(1:length(y)/2));
% ylabel('幅值的模');
% xlabel('时间(s)');
% title('原始信号傅里叶变换');
% %用周期图法估计功率谱密度
% p=y.*conj(y)/1000; %计算功率谱密度
% ff=10000*(0:499)/1000; %计算变换后不同点对应的频率值
% figure(2);
% plot(ff,p(1:500));
% ylabel('幅值');
% xlabel('频率(Hz)');
% title('功率谱密度（周期图法）');


