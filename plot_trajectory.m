clc;
clear all;
close all;

data = load('build/KITTI_00.txt');
num_frames = size(data, 1);
num_poses = 300;

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
   T_w_c = [reshape(T_flat, 4, 3)'; 0 0 0 1];
   T_c_w = inv(T_w_c);
   T_c_n = T_n_w * T_c_w;
   R{i} = T_c_n(1:3, 1:3);
   t_cell{i} = T_c_n(1:3,4);
   t(:,i) = t_cell{i};
end

gt_arr = load('data/00/poses.txt');
for i = 1:num_poses
    gt_flat = gt_arr(i,:);
    T_w_c = [reshape(gt_flat, 4, 3)'; 0 0 0 1];
    gt_t(:,i) = T_w_c(1:3, 4);;
end

figure(1)
axis equal
grid on
hold on
scatter(t(1,:), t(2,:), 'r*');
scatter(gt_t(3,:), -gt_t(1,:), 'b*');
xlabel("Local N");
ylabel("Local W");
legend('Estimate', 'Ground Truth');
title("KITTI 00 Trajectory Estimate");