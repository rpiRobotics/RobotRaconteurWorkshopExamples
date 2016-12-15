clear variables; close all;

w = RobotRaconteur.Connect('tcp://localhost:2345/example.webcam/Webcam');

%%
im_h = w.getImageHeader();

figure(1); clf;
h = imshow(zeros(im_h.height,im_h.width,im_h.channels,'uint8'));

while (1)
    im = w.getCurrentImage();
    Ib = reshape(im.data(1:im_h.channels:end),[im.width im.height])';
    Ig = reshape(im.data(2:im_h.channels:end),[im.width im.height])';
    Ir = reshape(im.data(3:im_h.channels:end),[im.width im.height])';
    I = cat(3,Ir,Ig,Ib);
    figure(1);
    set(h,'CData',I);   
    pause(1/24);
    drawnow;
end
