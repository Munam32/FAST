% Coulomb's constant
k = 8.99e9; % Nm^2/C^2

% Input values from the user
q1 = input('Enter magnitude of charge 1 (C): ');
q2 = input('Enter magnitude of charge 2 (C): ');

% Distance vector
distance = linspace(1, 10, 100); % Adjust the range as needed

% Coulomb's force calculation
force = k * q1 * q2 ./ distance.^2;

% Plotting
figure;
plot(r, force, '-b', 'LineWidth', 2);
title('Force Graph');
xlabel('Distance (m)');
ylabel('Coulomb''s Force (N)');
grid on;

% Save the figure
saveas(gcf, 'lol 2.png');
