close all;
clear all;

% чтение изображения
img = imread('city_3.png');
% переводим изображение в оттенки серого
img = rgb2gray(img);

% выражаем контур с помощью встроенной функции edge
BW = edge(img);
figure, imshow(img);
figure, imshow(BW);

hy = fspecial('sobel');
hx = hy';

dimg_dy = imfilter(img, hy);
dimg_dx = imfilter(img, hx);

grad_angles = get_grad_angles(img, BW, dimg_dx, dimg_dy);

hst = get_histogram(grad_angles);

figure, bar(hst');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% разбиваем изображение на 3 части по горизонтали,
% для каждой части строим гисторамму
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
third_size = fix(size(img, 1) / 3);

img_part1 = img(1 : third_size, :);
img_part2 = img(third_size + 1 : size(img, 1) - third_size, :);
img_part3 = img(size(img, 1) - third_size + 1 : size(img, 1), :);

figure, imshow(img_part1);
figure, imshow(img_part2);
figure, imshow(img_part3);

BW_part1 = edge(img_part1);
BW_part2 = edge(img_part2);
BW_part3 = edge(img_part3);

dimg_dy_part1 = imfilter(img_part1, hy);
dimg_dx_part1 = imfilter(img_part1, hx);
dimg_dy_part2 = imfilter(img_part2, hy);
dimg_dx_part2 = imfilter(img_part2, hx);
dimg_dy_part3 = imfilter(img_part3, hy);
dimg_dx_part3 = imfilter(img_part3, hx);

grad_angles_part1 = get_grad_angles(img_part1, BW_part1, dimg_dx_part1, dimg_dy_part1);
grad_angles_part2 = get_grad_angles(img_part2, BW_part2, dimg_dx_part2, dimg_dy_part2);
grad_angles_part3 = get_grad_angles(img_part3, BW_part3, dimg_dx_part3, dimg_dy_part3);

hst_part1 = get_histogram(grad_angles_part1);
hst_part2 = get_histogram(grad_angles_part2);
hst_part3 = get_histogram(grad_angles_part3);

hst_part1(73) = size(grad_angles_part1, 2) / (size(img_part1, 1) * size(img_part1, 2));
hst_part2(73) = size(grad_angles_part2, 2) / (size(img_part2, 1) * size(img_part2, 2));
hst_part3(73) = size(grad_angles_part3, 2) / (size(img_part3, 1) * size(img_part3, 2));

full_hst = [hst_part1 hst_part2 hst_part3];
figure, bar(full_hst');

