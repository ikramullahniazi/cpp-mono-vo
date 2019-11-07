clc;
clear all;
close all;

data = load('results.txt');
num_frames = size(data, 1);

% Nav frame: NED
% World/Cam frame: z forward, x down

T_n_w = ...
    [0 0 1 0;
    -1 0 0 0;
    0 -1 0 0;
    0 0 0 1];

R = {};
t_cell = {};
t = [];


for i = 1:num_frames
   T_flat = data(i,:);
   T_w_c = reshape(T_flat, 4, 4)';
   T_c_w = inv(T_w_c);
   T_c_n = T_n_w * T_c_w;
   R{i} = T_c_n(1:3, 1:3);
   t_cell{i} = T_c_n(1:3,4);
   t(:,i) = t_cell{i};
end

figure(1)
axis equal
grid on
scatter(t(1,:), t(2,:), 'r*');
xlabel("Local N");
ylabel("Local W");