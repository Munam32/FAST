
g = 9.81; % acceleration due to gravity (m/s^2)
v0 = 5; % initial velocity (m/s)

% Angles in radians
theta1 = 30 * pi / 180;
theta2 = 45 * pi / 180;
theta3 = 60 * pi / 180;

% % Calculate time of flight for each angle
% t1 = 2 * v0 * sin(theta1) / g;
% t2 = 2 * v0 * sin(theta2) / g;
% t3 = 2 * v0 * sin(theta3) / g;

% max range
r1 = (v0.^2 * sin(2*theta1))/g ;
r2 = (v0.^2 * sin(2*theta2))/g ;
r3 = (v0.^2 * sin(2*theta3))/g ;
 

% Calculate x and y values for each angle
% t = linspace(0, max( [t1, t2, t3] ), 100); % finding max time value to plot
% x1 = v0 * cos(theta1) * t;
% y1 = v0 * sin(theta1) * t - 0.5 * g * t.^2;
% 
% x2 = v0 * cos(theta2) * t;
% y2 = v0 * sin(theta2) * t - 0.5 * g * t.^2;
% 
% x3 = v0 * cos(theta3) * t;
% y3 = v0 * sin(theta3) * t - 0.5 * g * t.^2;

r1_p = linspace(0,r1,20);
r2_p = linspace(0,r2,20);
r3_p = linspace(0,r3,20);

y1 =  (tan(theta1)*r1_p) - ( g / (2 *( v0 * cos(theta1) ).^2) )*r1_p.^2;
y2 =  (tan(theta2)*r2_p) - ( g / (2 *( v0 * cos(theta2) ).^2) )*r2_p.^2;
y3 =  (tan(theta3)*r3_p) - ( g / (2 *( v0 * cos(theta3) ).^2) )*r3_p.^2;


% Plotting
figure;
hold on;
plot(r1_p, y1, 'g', 'LineWidth', 1.5);

plot(r2_p, y2, 'r', 'LineWidth', 1.5);
plot(r3_p, y3, 'b', 'LineWidth', 1.5);
xlabel('Horizontal Displacement /x (m)');
ylabel('Vertical Displacement /y (m)');
title('Projectile Trajectories');
legend('\theta = 30^\circ', '\theta = 45^\circ', '\theta = 60^\circ');
grid on;


% Save the plot as an image
saveas(gcf, 'lol.png');
