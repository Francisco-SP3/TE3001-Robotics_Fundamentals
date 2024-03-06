dbstop if error
clear all;
clc;
close all;

% Motor parameters
tau = 0.5;
k   = 0.3;
%

% Initial Conditions 
IC      = [0;0];  
%

% Time interval
TINT    = 0:0.001:50;
%

[t,state] = ode45(@(t,state) mysolver(t, state, tau, k),TINT,IC);

omega = state(:,1);
z     = state(:,2);

figure
plot(t,omega)
omegamax = max(omega);
omegamin = min(omega);
axis([t(1,1), t(end,1), omegamin-omegamax*0.1, omegamax*1.1]);
xlabel('time')
ylabel('rad/s')
title('DC Motor angular velocity')

% MODIFY THIS ACCORDING TO THE CONTROL INPUT!!!
kp = 5;
ki = 1;
omegad = 5;
[ren,~] = size(t);
for index = 1:1:ren
    u(index,1) = kp*(omegad - omega(index,1)) + z(index,1);
end

figure
plot(t,u)
umax = max(u);
umin = min(u);
axis([t(1,1), t(end,1), umin-umax*0.1, umax*1.1]);
xlabel('time')
ylabel('volts')
title('Control Input')

%save('DCM_PI_kp_1_ki_1.mat','omega','u','t');

 
function dstatedt = mysolver(t, state, tau, k)
 
    omega = state(1,1);
    z     = state(2,1);
    
    % The controller u(t)
        kp = 5;
        ki = 1;
        omegad = 5;
        u    = kp*(omegad - omega) + z;
        zdot = ki*(omegad - omega);
    %

    % The differential equation 
    omegadot = -tau*omega + k*u;
    %

    dstatedt = [omegadot; zdot];     
     
    display(t)
 end
