% ������Ƶ
[y1, sr1]=audioread('1_r.wav');
%sound(y1, sr1);
[f1] = v_enframe(y1, hanning(110364, 'periodic'));
sound(f1, sr1);
% ����Ҷ�任
Y1_FFT = fft(y1);

m1 = abs(Y1_FFT');
m2 = zeros(1, length(m1));

m2(1, :) = (m1(1, :)-min(m1(:)))/(max(m1(:))-min(m1(:)));

m3 = m2';


% m2 = abs(Y2_FFT');

n = length(m1(1,:));
f = (0:n-1)*(sr1/n);
plot(f(1:n/2), m1(1:n/2));
xlabel('Frequency');
ylabel('Amplitude');




% y0 = fftshift(Y1_FFT);
% f0 = (-n/2:n/2-1)*(sr1/n);
% m0 = abs(y0);
% plot(f0, m0);





%���ȣ�������ֵ
%mag_max=max(m1(1,1:N/2));
% %������ֵ����Ӧ��Ƶ�ʣ����������Ƶ��
%fre_max=find(m1(1, 1:N/2)==mag_max);
%fre_max=round(fre_max*sr1/N);
% fre_max=round(fre_max*sr1/N);
% i = 1:1:530;
% plot(i, m1(i, :), 'b-', i, m2(i, :), 'y-');


% f1 = (0:length(Y1_FFT)/2-1) * sr1/length(Y1_FFT);
% plot(f1,m(1:length(y)/2));
% 
% % ��������
% res = Y1_FFT .* conj(Y2_FFT);






% t=0:0.0001:0.1; %ʱ����Ϊ0.0001��˵������Ƶ��Ϊ10000Hz
% x=square(2*pi*1000*t); %������ƵΪ1000Hz�ķ����ź�
% n=randn(size(t)); %������
% f=x+n; %���ź��м��������
% figure(1);
% subplot(2,1,1);
% plot(f); %����ԭʼ�źŵĲ���ͼ
% ylabel('��ֵ(V)');
% xlabel('ʱ��(s)');
% title('ԭʼ�ź�');
% y=fft(f,1000); %��ԭʼ�źŽ�����ɢ����Ҷ�任���μ�DFT������ĸ���Ϊ1000
% subplot(2,1,2);
% m=abs(y);
% f1=(0:length(y)/2-1)'*10000/length(y);%����任��ͬ���Ӧ�ķ�ֵ
% plot(f1,m(1:length(y)/2));
% ylabel('��ֵ��ģ');
% xlabel('ʱ��(s)');
% title('ԭʼ�źŸ���Ҷ�任');
% %������ͼ�����ƹ������ܶ�
% p=y.*conj(y)/1000; %���㹦�����ܶ�
% ff=10000*(0:499)/1000; %����任��ͬ���Ӧ��Ƶ��ֵ
% figure(2);
% plot(ff,p(1:500));
% ylabel('��ֵ');
% xlabel('Ƶ��(Hz)');
% title('�������ܶȣ�����ͼ����');


