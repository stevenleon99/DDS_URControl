function [xi,theta,w,v,A,S,T] = getXi(g)
% Take a homogenous transformation matrix and extract the unscaled twist
% input g: a homogeneous transformation 
% xi: the (un-normalized) twist in 6 × 1 vector or twist coordinate
% updated theta threshould by Yinsong 20231214
R = g(1:3,1:3);
P = g(1:3,4);
I = eye(3);
xi = zeros(6,1);
% rotation part
theta = acos((trace(R)-1)/2);
if theta < 0.001
    xi(1:3) = P;
    return;
else    
    if theta == pi
        test = [R(1,1),R(2,2),R(3,3)];
        [M,I1] = max(test);
        xi(I1+3,1) = pi;
        w = xi(4:6)/pi;
    else
        W_hat = 1/(2*sin(theta))*(R-R');
        w = [-W_hat(2,3);W_hat(1,3);-W_hat(1,2)];
        xi(4:6,1) = w*theta;
    end
end

% transition part
A = (I-R)*SKEW3(w)+w*w'*theta;
v = A\P;
xi(1:3,1) = v*theta;

end