function [x, y] = mouseMovement()
    loc = get(0, 'PointerLocation');
    x = loc(1);
    y = loc(2);
end