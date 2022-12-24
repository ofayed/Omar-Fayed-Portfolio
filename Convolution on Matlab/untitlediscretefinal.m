
clc
clear
close all

sign = "Choose your input signal x(n): ";
choice = "Enter which signal you want 1.square 2. exp(exponential) 3. triangulaPulse 4.heaviside(Unit step function)";
txt = input(choice,"s");

initial = "Enter initial t: ";
tint = input(initial, 's');
tint2 = sscanf(tint, '%f', 1);
disp(tint2)

final = "Enter final t: ";
tfinal = input(final, 's');
tfinal2 = sscanf(tfinal, '%f', 1);
disp(tfinal2)

step = "Enter step: ";
tstep = input(step, 's');
tstep2 = sscanf(tstep, '%f', 1);
disp(tstep2)

amp = "Enter vertical amplification: ";
tamp = input(amp, 's');
tamp2 = sscanf(tamp, '%f', 1);
disp(tamp2)

hamps = "Enter horizontal amplification: ";
hamp = input(hamps, 's');
hamp2 = sscanf(hamp, '%f', 1);

hshift = "Enter horizontal shift: ";
hshifts = input(hshift, 's');
hshifts2 = sscanf(hshifts, '%f', 1);

vshift = "Enter vertical shift: ";
vshifts = input(vshift, 's');
vishifts2 = sscanf(vshifts, '%f', 1);
disp(hamp2)

disp(txt)

 
sign2 = "Choose your input signal h(n): ";
choice2 = "Enter which signal you want 1.square 2. exp(exponential) 3. triangulaPulse 4.heaviside(Unit step function)";
txt2 = input(choice2,"s");

hinitial = "Enter initial t: ";
hint = input(hinitial, 's');
hint2 = sscanf(hint, '%f', 1);
disp(hint2)

hfinal = "Enter final t: ";
hfinall = input(hfinal, 's');
hfinal2 = sscanf(hfinall, '%f', 1);
disp(hfinal2)

hstep = "Enter step: ";
hstepp = input(hstep, 's');
hstep2 = sscanf(hstep, '%f', 1);
disp(hstep2)

hampp = "Enter vertical amplification: ";
hamp = input(hampp, 's');
hamp2 = sscanf(hamp, '%f', 1);
disp(hamp2)

hhamps = "Enter horizontal amplification: ";
hhamp = input(hhamps, 's');
hhamp2 = sscanf(hhamp, '%f', 1);
disp(hhamp2)

hhshift = "Enter horizontal shift: ";
hhshifts = input(hhshift, 's');
hhshifts2 = sscanf(hhshifts, '%f', 1);

hvshift = "Enter vertical shift: ";
hvshifts = input(hvshift, 's');
hvishifts2 = sscanf(hvshifts, '%f', 1);

disp(txt2)

%t2 = hint2 : hstep2 : hfinal2;
 t = tint2 : tstep2 : tfinal2;
if(txt == "square")
    X = ((tamp2 *(square(hamp2*t - hshifts2))) - vishifts2);
else 
    if(txt == "exp") 
        X = ((tamp2 *(exp(hamp2*t - hshifts2))) - vishifts2);
    else
        if(txt == "heaviside")
               X = ((tamp2 *(heaviside(hamp2*t - hshifts2 ))) - vishifts2); 
                
        else
               X = ((hamp2 *triangularPulse( (hhamp2*t - hhshifts2)) )-hvishifts2); 
        end
    end
end

if(txt2 == "square")
    H = ((hamp2 *(square(hhamp2*t - hhshifts2)))-hvishifts2);
else 
    if(txt2 == "exp") 
        H = ((hamp2 *(exp( (hhamp2*t - hhshifts2) )))-hvishifts2);
    else
            if(txt2 == "heaviside")
               H = ((hamp2 *heaviside( (hhamp2*t - hhshifts2)) )-hvishifts2); 
                
            else
               H = ((hamp2 *triangularPulse( (hhamp2*t - hhshifts2)) )-hvishifts2); 
            end
    end
end


%H = 400 * exp( (-400*t) ); 
subplot( 3, 1, 1);
 stem( t, X);
 subplot( 3, 1, 2);
 stem( t, H);

for i=1:length(t)
    Y(i)=0;
    for j=1:numel(t)
        if(i-j+1>0)
            Y(i)=Y(i)+X(j)*H(i-j+1);
        else
        end
    end
end
subplot( 3, 1, 3);
 stem( t, Y);

