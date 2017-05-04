clear all;
close all;

% чтение изображения
img = imread('coins.png');

% вывести исходное изображение на экран
figure, imshow(img);
title('Image');

% вывести на экран гистограмму исходного изображения
figure, imhist(img);
title('Image histogam');

% значение яркости, относительно которой делается бинаризация
brightness = 100;

% копия изображения для общей бинаризации
img_bw = img;

% размер изображения
[N M] = size(img);

% общая бинаризация
for i = 1:N
    for j = 1:M
        if img_bw(i, j) < brightness
            img_bw(i, j) = 0;
        else
            img_bw(i, j) = 255;
        end
    end
end

% вывести на экран изображение после общей бинаризации
figure, imshow(img_bw);
title('Image after common binarization');

% размер окна для локальной бинаризации
window_size = 60;
% рамка для изображения с размером в половину окна
img_local = padarray(img, [window_size/2 window_size/2], 'symmetric');

% локальная бинаризация
for i = window_size/2:N+window_size/2
    for j = window_size/2:M+window_size/2
            mean_brightness = mean2(img_local(i - window_size / 2 + 1 : i + window_size / 2, j - window_size / 2 + 1 : j + window_size / 2));
            
            if img_local(i - window_size / 2 + window_size / 2, j - window_size / 2 + window_size / 2) <= mean_brightness
                img_local(i - window_size / 2 + window_size / 2, j - window_size / 2 + window_size / 2) = 0;
            else
                img_local(i - window_size / 2 + window_size / 2, j - window_size / 2 + window_size / 2) = 255;
            end
    end
end

% вывести изображение на экран после локальной бинаризации
figure, imshow(img_local);
title('Image after local binarization');

% копия изображения для дилатации
img_dil = img_local(window_size / 2 + 1 : size(img_local, 1) - window_size / 2, window_size / 2 + 1 : size(img_local, 2) - window_size / 2);
% размер окна для дилатации
window_size = 3;

img_bw = padarray(img_bw, [fix(window_size/2) fix(window_size/2)]);
img_dil = img_bw;

% дилатация
for i = fix(window_size / 2) + 1:N-1
    for j = fix(window_size / 2) + 1:M-1
        isWhite = false;
        
        for k = i:i+window_size
            for l = j:j+window_size
                if img_bw(k, l) == 255
                    isWhite = true;
                end
            end
        end
        
        if isWhite == true
            img_dil(i + fix(window_size / 2), j + fix(window_size / 2)) = 255;
        end
    end
end


% вывести на экран изображение после дилатации
figure, imshow(img_dil);
title('Image after dilatation');


img_ero = img_dil;

% эрозия
for i = fix(window_size / 2) + 1:N-1
    for j = fix(window_size / 2) + 1:M-1
        isBlack = false;
        
        for k = i:i+window_size
            for l = j:j+window_size
                if img_dil(k, l) == 0
                    isBlack = true;
                end
            end
        end
        
        if isBlack == true
            img_ero(i + fix(window_size / 2), j + fix(window_size / 2)) = 0;
        end
    end
end

% вывести на экран изображение после дилатации
figure, imshow(img_ero);
title('Image after erosion');

% разность между изображением после дилатации и изображением после эрозии
minus = img_dil - img_ero;

% вывести изображение разности
figure, imshow(minus);
title('Difference between dilatated image and erosed image');
