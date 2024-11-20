
classdef MotionGenerator  < handle % matlab.System
    
    properties (SetAccess = private)
        maxVel = 0;
        maxAcc = 0;
        pos = 0; % desired output position
        vel = 0; % desired output veloctiy
        % acc = 0; % desired output acceleration
        oldPos = 0; % input with real output position
        oldPosRef = 0; % input with target position
        oldVel = 0;
        
        distanceBrake = 0;
        distanceAccelerate = 0;
        distanceConstVelocity = 0;
        distanceDecelerate = 0;
        distanceTotal = 0;
        
        timeBrake = 0;
        timeAccelerate = 0;
        timeConstVelocity = 0;
        timeDecelerate = 0;
        
        velTop = 0;
        
        oldTime = 0;
        lastTime = 0;
        deltaTime = 0;
        
        signM = 1;      % 1 = positive change, -1 = negative change
        shape = 1;      % 1 = trapezoidal, 0 = triangular
        
    end
    
    methods
        % =================================================================
        % Constructor
        function MG = MotionGenerator(aVelMax,aAccMax,aPosInit)
            MG.maxVel       = aVelMax;
            MG.maxAcc       = aAccMax;
            MG.oldPos       = aPosInit;
            MG.oldPosRef    = aPosInit;
            MG.pos          = aPosInit; 
        end
        
        % =================================================================
        % Public methods
        function update(MG, posRef, time)
            
            if (MG.oldPosRef ~= posRef)  % reference changed
                % Shift state variables
                MG.oldPosRef = posRef;
                MG.oldPos = MG.pos;
                MG.oldVel = MG.vel;
                MG.oldTime = MG.lastTime;
                
                % Calculate braking time and distance (in case is neeeded)
                MG.timeBrake = abs(MG.oldVel) / MG.maxAcc; % same as for shape = 0
                MG.distanceBrake = MG.timeBrake * abs(MG.oldVel) / 2;
                
                % Caculate Sign of motion
                MG.signM = sign(posRef - (MG.oldPos + sign(MG.oldVel)*MG.distanceBrake));
                
                if (MG.signM ~= sign(MG.oldVel))  % means brake is needed
                    MG.timeAccelerate = (MG.maxVel / MG.maxAcc);
                    MG.distanceAccelerate = MG.timeAccelerate * (MG.maxVel / 2);
                else
                    MG.timeBrake = 0;
                    MG.distanceBrake = 0;
                    MG.timeAccelerate = (MG.maxVel - abs(MG.oldVel)) / MG.maxAcc;
                    MG.distanceAccelerate = MG.timeAccelerate * (MG.maxVel + abs(MG.oldVel)) / 2;
                end
                
                % Calculate total distance to go after braking
                MG.distanceTotal = abs(posRef - MG.oldPos + MG.signM*MG.distanceBrake);
                
                MG.timeDecelerate = MG.maxVel / MG.maxAcc;
                MG.distanceDecelerate = MG.timeDecelerate * (MG.maxVel) / 2;
                MG.distanceConstVelocity = MG.distanceTotal - (MG.distanceAccelerate + MG.distanceDecelerate);
                MG.timeConstVelocity = MG.distanceConstVelocity / MG.maxVel;
                
                if (MG.timeConstVelocity > 0)    % trapezoidal shape
                    MG.shape = 1;
                else                % triangular shape
                    MG.shape = 0;
                    % Recalculate distances and periods
                    if (MG.signM ~= sign(MG.oldVel))  % means brake is needed
                        MG.velTop = sqrt(MG.maxAcc*(MG.distanceTotal));
                        MG.timeAccelerate = (MG.velTop / MG.maxAcc);
                        MG.distanceAccelerate = MG.timeAccelerate * (MG.velTop / 2);
                    else
                        MG.timeBrake = 0;
                        MG.distanceBrake = 0;
                        MG.distanceTotal = abs(posRef - MG.oldPos);      % recalculate total distance
                        MG.velTop = sqrt(0.5*MG.oldVel^2 + MG.maxAcc*MG.distanceTotal);
                        MG.timeAccelerate = (MG.velTop - abs(MG.oldVel)) / MG.maxAcc;
                        MG.distanceAccelerate = MG.timeAccelerate * (MG.velTop + abs(MG.oldVel)) / 2;
                    end
                    MG.timeDecelerate = MG.velTop / MG.maxAcc;
                    MG.distanceDecelerate = MG.timeDecelerate * (MG.velTop) / 2;
                end
                
            end
            
            % Calculate time since last set-point change
            MG.deltaTime = (time - MG.oldTime);
            % Calculate new setpoint
            MG.calculateTrapezoidalProfile(posRef);
            % Update last time
            MG.lastTime = time;
            
        end
        % =================================================================
        function calculateTrapezoidalProfile(MG, posRef)
            
            t = MG.deltaTime;
            
            if (MG.shape)   % trapezoidal shape
                if (t <= (MG.timeBrake+MG.timeAccelerate))
                    MG.pos = MG.oldPos + MG.oldVel*t + MG.signM * 0.5*MG.maxAcc*t^2;
                    MG.vel = MG.oldVel + MG.signM * MG.maxAcc*t;
                    % MG.acc = MG.signM * MG.maxAcc;
                elseif (t > (MG.timeBrake+MG.timeAccelerate) && t < (MG.timeBrake+MG.timeAccelerate+MG.timeConstVelocity))
                    MG.pos = MG.oldPos + MG.signM * (-MG.distanceBrake + MG.distanceAccelerate + MG.maxVel*(t-MG.timeBrake-MG.timeAccelerate));
                    MG.vel = MG.signM * MG.maxVel;
                    % MG.acc = 0;
                elseif (t >= (MG.timeBrake+MG.timeAccelerate+MG.timeConstVelocity) && t < (MG.timeBrake+MG.timeAccelerate+MG.timeConstVelocity+MG.timeDecelerate))
                    MG.pos = MG.oldPos + MG.signM * (-MG.distanceBrake + MG.distanceAccelerate + MG.distanceConstVelocity + MG.maxVel*(t-MG.timeBrake-MG.timeAccelerate-MG.timeConstVelocity) - 0.5*MG.maxAcc*(t-MG.timeBrake-MG.timeAccelerate-MG.timeConstVelocity)^2);
                    MG.vel = MG.signM * (MG.maxVel - MG.maxAcc*(t-MG.timeBrake-MG.timeAccelerate-MG.timeConstVelocity));
                    % MG.acc = - MG.signM * MG.maxAcc;
                else
                    MG.pos = posRef;
                    MG.vel = 0;
                    % MG.acc = 0;
                end
            else            % triangular shape
                if (t <= (MG.timeBrake+MG.timeAccelerate))
                    MG.pos = MG.oldPos + MG.oldVel*t + MG.signM * 0.5*MG.maxAcc*t^2;
                    MG.vel = MG.oldVel + MG.signM * MG.maxAcc*t;
                    % MG.acc = MG.signM * MG.maxAcc;
                elseif (t > (MG.timeBrake+MG.timeAccelerate) && t < (MG.timeBrake+MG.timeAccelerate+MG.timeDecelerate))
                    MG.pos = MG.oldPos + MG.signM * (-MG.distanceBrake + MG.distanceAccelerate + MG.velTop*(t-MG.timeBrake-MG.timeAccelerate) - 0.5*MG.maxAcc*(t-MG.timeBrake-MG.timeAccelerate)^2);
                    MG.vel = MG.signM * (MG.velTop - MG.maxAcc*(t-MG.timeBrake-MG.timeAccelerate));
                    % MG.acc = - MG.signM * MG.maxAcc;
                else
                    MG.pos = posRef;
                    MG.vel = 0;
                    % MG.acc = 0;
                end
                
            end
            
        end
        
    end
end