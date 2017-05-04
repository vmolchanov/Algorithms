function [grad_angles] = get_grad_angles(img, BW, dimg_dx, dimg_dy)
    % счетчик
    k = 1;
    
    for i = 1:size(img, 1)
        for j = 1:size(img, 2)
            if BW(i, j) == 1
                if dimg_dx(i, j) == 0
                    grad_angles(k) = 0;
                else
                    grad_angles(k) = atan(double(dimg_dy(i, j)) / double(dimg_dx(i, j)));
                    % переводим угол из радиан в градусы
                    grad_angles(k) = grad_angles(k) * 180 / pi;
                end
                k = k + 1;
            end
        end
    end
end