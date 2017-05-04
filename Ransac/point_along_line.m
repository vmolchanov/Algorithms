function [xpoints ypoints] = point_along_line(POINTS_COUNT, MIN_VALUE, MAX_VALUE)

    xpoints = zeros(POINTS_COUNT, 1);
    ypoints = zeros(POINTS_COUNT, 1);
    x_line = 1:POINTS_COUNT - 50;
    k = get_rand_num(1, 1, -10, 10);
    b = get_rand_num(1, 1, 1, 20);
    y_line = k * x_line + b;

    for i = 1 : POINTS_COUNT - fix(POINTS_COUNT / 3)
        xpoints(i) = x_line(i);
        ypoints(i) = y_line(i);
    end

    for i = POINTS_COUNT - (fix(POINTS_COUNT / 3) - 1) : POINTS_COUNT
        xx = get_rand_num(1, 1, MIN_VALUE, MAX_VALUE);
        yy = get_rand_num(1, 1, MIN_VALUE, MAX_VALUE);

        xpoints(i) = xx;
        ypoints(i) = yy;
    end

end
