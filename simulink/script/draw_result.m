y = out.simout1.Data;
x = linspace(0, size(y, 1), size(y, 1));
plot(x, y);
title("MG velocity");

y2 = [0 y'];
y3 = [y' 0];
diff = y2 - y3;
x2 = linspace(0, size(y3, 1), size(y3, 1));
plot(x2, diff);
title("difference velocity");