% g_k actual position rigid transformation matrix SE(3)
% g_des desired position rigid transformation matrix SE(3)
% return orientation error: err_r position error: err_p

function finalerr = reportError(g_k, g_des)

    r_k = g_k(1:3, 1:3); 
    r_des = g_des(1:3, 1:3);
    pos_k = g_k(1:3, 4);
    pos_des = g_des(1:3, 4);
    err_r = sqrt(trace((r_k - r_des)*transpose(r_k - r_des)));
    err_p = 100 * norm(pos_des - pos_k);

    disp("orientation error SO(3): ");
    disp(err_r);
    disp("destination error p: ");
    disp(err_p);

    finalerr = [err_r; err_p];

end