data = load("data.txt");

input_1 = data(1:6:end);
input_1 = input_1 - mean(input_1(1:5000));

input_2 = data(2:6:end);
input_2 = input_2 - mean(input_2(1:5000));

input_3 = data(3:6:end);
input_3 = input_3 - mean(input_3(1:5000));

input_4 = data(4:6:end);
input_4 = input_4 - mean(input_4(1:5000));

input_5 = data(5:6:end);
input_5 = input_5 - mean(input_5(1:5000));

input_6 = data(6:6:end);
input_6 = input_6 - mean(input_6(1:5000));


input = [input_1 input_2 input_3 input_4 input_5 input_6];



calibrationMatrix = [ 0.02635,   0.05725, -0.16898, -3.36272,   0.15990,   3.37204;
    0.03966,   3.97255, -0.15251, -1.87075, -0.07907, -2.01298;
    3.75948, -0.06271,   3.78516, -0.05606,   3.78257, -0.19971;
    -0.51569,  24.65602,  19.68848, -11.89616, -21.76668, -11.40450 ;
    -24.92166,   0.09261,  12.63655,  20.64617,  11.45515, -21.56128;
   0.09156,  14.93053,   0.64898,  14.11840,   0.84995,  15.11919];


force = calibrationMatrix * input';
figure(1)
hold on
grid on
subplot(3,1,1)
plot(force(1,:))
ylabel("Force X ")

subplot(3,1,2)
plot(force(2,:))
ylabel("Force Y")

subplot(3,1,3)
plot(force(3,:))
ylabel("Force Z")


figure(2)
subplot(3,1,1)
plot(force(4,:))
ylabel("Torque X")

subplot(3,1,2)
plot(force(5,:))
ylabel("Torque Y")

subplot(3,1,3)
plot(force(6,:))
ylabel("Torque Z")

