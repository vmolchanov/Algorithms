clear all
close all

POINTS_COUNT = 150;
MIN_VALUE = 0;
MAX_VALUE = 400;
N = Inf;
GAP = 20;

[xpoints ypoints] = point_along_line(POINTS_COUNT, MIN_VALUE, MAX_VALUE);

% индекс первой точки для лучшей выборки
ipoint1_max = 0;
% индекс второй точки для лучшей выборки
ipoint2_max = 0;
% количество точек в окрестности прямой для лучшей выборки
gap_points_count_max = -1;
% вероятность, что хотя бы одна выборка будет без выбросов
p = 0.99;
% количество степеней свободы
s = 2;
% количество итераций
k = 0;

while k < N
    
    err_func = [];
    gap_points_count = 0;
   
    % выбираем две рандомные точки
    ipoint1 = get_rand_num(1, 1, 1, size(xpoints, 1));
    ipoint2 = get_rand_num(1, 1, 1, size(xpoints, 1));
    
    % считаем функцию ошибки
    for i = 1 : size(xpoints, 1)
       
        if (i ~= ipoint1 && i ~= ipoint2)
            % находим стороны треугольника
            a = sqrt( (xpoints(i) - xpoints(ipoint1))^2 + (ypoints(i) - ypoints(ipoint1))^2 );
            b = sqrt( (xpoints(ipoint1) - xpoints(ipoint2))^2 + (ypoints(ipoint1) - ypoints(ipoint2))^2 );
            c = sqrt( (xpoints(i) - xpoints(ipoint2))^2 + (ypoints(i) - ypoints(ipoint2))^2 );
            % полупериметр треугольника
            sp = (a + b + c) / 2;
            % площадь треугольника
            square = sqrt( sp * (sp - a) * (sp - b) * (sp - c) );
            
            err_func = [err_func (2 * square / b)];
            
            if 2 * square / b <= GAP
                gap_points_count = gap_points_count + 1;
            end
        end
        
    end
    
    if gap_points_count > gap_points_count_max || gap_points_count_max == -1
        ipoint1_max = ipoint1;
        ipoint2_max = ipoint2;
        gap_points_count_max = gap_points_count;
    end
    
    k = k + 1;
    e = 1 - gap_points_count / POINTS_COUNT;
    N = log10(1 - p) / log10(1 - (1 - e)^s);
    
end

% строим график с сгенерированными точками и аппроксимирующую прямую
figure, plot(xpoints, ypoints, '.');
hold on;
plot([xpoints(ipoint1_max) xpoints(ipoint2_max)], [ypoints(ipoint1_max) ypoints(ipoint2_max)], '-r');













