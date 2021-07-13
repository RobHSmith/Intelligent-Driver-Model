%Rob Smith
%5/18/2021

%housekeeping
clear
clc
close all hidden

%read in data as table
datat = readtable('motion.csv');

%convert data to matrix
data = cell2mat({table2array(datat)});

%extract time data
t = data(1:end,1);

%find number of vehicles and traffic lights
[simsteps,colnum] = size(data);

numlight = 6;

numveh = (colnum-1-(numlight*2))/4;

%set light data to not plot times that the light is green
for r = 1:simsteps
    for g = 1:numlight
        if data(r,(4*numveh)+2*g) == 0
            data(r,(4*numveh)+2*g) = NaN;
        end
        if data(r,(4*numveh+1)+2*g) == 0
            data(r,(4*numveh+1)+2*g) = NaN;
        end
    end
end

%create modified matrix of light data for plotting
light = data(:,(4*numveh+2):colnum);

[lstep,lcol] = size(light);

for s = 1:lcol
    for w = 1:lstep
        if ~isnan(light(w,s))
            light(w,s) = 0;
        end
    end
end

%preallocate legend arrays
strcars = strings([1 numveh+2]);
strgap = strings([1 numveh+1]);

%plot vehicle attributes
for i = 1:numveh
    %plot acceleration commands
    figure(1)
    hold on
    plot(t,data(:,4*i-2))
    
    %plot velocity
    figure(2)
    hold on
    plot(t,data(:,4*i-1))
    
    %plot position
    figure(3)
    hold on
    plot(t,data(:,4*i+1))
    
    %add to legend array
    strcars{i} = sprintf('Vehicle %d',i);
end

%plot gap
for j = 2:numveh
    figure(4)
    hold on
    plot(t,data(:,4*j))
    
    %add to legend array
    strgap{j-1} = sprintf('Vehicle %d',j);
end

%plot lights
%for n = 1:4   %<-- This set of loops for if lights shown on multiple plots
    %for k = 1:numlight
        %if n ~=3
            %figure(n)
            %scatter(t,light(:,1),10,'Yellow','filled')
            %scatter(t,light(:,2),10,'Red','filled')
        %else
            %figure(3)
            %scatter(t,data(:,(4*numcar)+2*k),2,'Yellow','filled')
            %scatter(t,data(:,(4*numcar+1)+2*k),2,'Red','filled')
        %end
    %end
%end

for k = 1:numlight
    figure(3)
    scatter(t,data(:,(4*numveh)+2*k),2,'Yellow','filled')
    scatter(t,data(:,(4*numveh+1)+2*k),2,'Red','filled')
end

strcars(numveh+1) = 'Yellow Light';
strcars(numveh+2) = 'Red Light';
%strgap(numcar) = 'Yellow Light'; %for lights plotted on gap plot
%strgap(numcar+1) = 'Red Light'; %for lights plotted on gap plot

%format plots
figure(1)
title('Acceleration Commands')
ylabel('Acceleration (m/s^2)')
xlabel('Time (s)')
legend(strcars,'Location','eastoutside')

figure(2)
title('Velocities')
ylabel('Velocity (m/s)')
xlabel('Time (s)')
legend(strcars,'Location','eastoutside')

figure(3)
title('Positions')
ylabel('Position (m)')
xlabel('Time (s)')
legend(strcars,'Location','eastoutside')

figure(4)
title('Gap Between Cars')
ylabel('Gap (m)')
xlabel('Time(s)')
legend(strgap,'Location','eastoutside')
    
    
