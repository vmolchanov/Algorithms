function [hst] = get_histogram(grad_angles)
    hst = zeros(1, 72);

    for i = 1:size(grad_angles, 2)
        hst(ceil(grad_angles(i) / 5) + 1) = hst(ceil(grad_angles(i) / 5) + 1) + 1;
    end

    hst = hst / size(grad_angles, 2);
end