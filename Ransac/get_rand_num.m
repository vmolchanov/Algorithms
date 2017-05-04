function [arr] = get_rand_num(n, m, min, max)
    arr = min + rand(n, m) * (max - min);
    arr = floor(arr);
end
