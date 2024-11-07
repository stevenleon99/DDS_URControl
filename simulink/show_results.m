% show result
if (exist("out", "var"))
    res = out.simout.Data;
    % rotate matrix to angle rx[] ry[] rz[]
    % position resuslt x[] y[] z[]
    ax = []; ay = []; az = [];
    px = []; py = []; pz = [];
    for i = 1 : size(res, 3)
        rotm = res(:, :, i);
        angles = rotm2eul(rotm(1:3, 1:3), "XYZ");
        px = [px, rotm(1,4)];
        py = [py, rotm(2,4)];
        pz = [pz, rotm(3,4)];
        ax = [ax, angles(1)];
        ay = [ay, angles(2)];
        az = [az, angles(3)];
    end
    draw(res,px,py,pz,ax,ay,az);


else
    disp("please run simulation first");

end

function draw(res,px,py,pz,ax,ay,az)
    subplot(2, 3, 1)
    x = linspace(0, size(res, 3), size(res, 3));
    plot(x, px);
    title("position x")
    subplot(2, 3, 2)
    y = linspace(0, size(res, 3), size(res, 3));
    plot(y, py);
    title("position y")
    subplot(2, 3, 3)
    z = linspace(0, size(res, 3), size(res, 3));
    plot(z, pz);
    title("position z")
    subplot(2, 3, 4)
    x2 = linspace(0, size(res, 3), size(res, 3));
    plot(x2, ax);
    title("angle x")
    subplot(2, 3, 5)
    y2 = linspace(0, size(res, 3), size(res, 3));
    plot(y2, ay);
    title("angle y")
    subplot(2, 3, 6)
    z2 = linspace(0, size(res, 3), size(res, 3));
    plot(z2, az);
    title("angle z")
end