function [f1]=function1(x,f1)
    	f1=(x(1,1)*x(1,1)-x(2,1)*x(2,1)-1);
endfunction
function [f2]=function2(x,f2)
    	f2=(x(1,1)*x(2,1)*x(2,1)*x(2,1)-x(2,1)-3);
endfunction 
function [der11]=derivative11(x,der11)
    	der11=(2*x(1,1));
endfunction 
function [der12]=derivative12(x,der12)
    	der12=(2*x(2,1));
endfunction 
function [der21]=derivative21(x,der21)
    	der21=(x(2,1)*x(2,1)*x(2,1));
endfunction 
function [der22]=derivative22(x,der22)
    	der22=(3*x(1,1)*x(2,1)*x(2,1)-1);
endfunction
function [ma]=findmax(no,ar,ma,cu)
    ma=cu;
    for i=cu:no
        if abs(ar(ma,cu))<abs(ar(i,cu)) then
            ma=i;
        end
    end
endfunction
function [ar,Y]=swap(cu,ma,ar,Y,no)
    if(ma ~= cu) then
        for i=cu:no
            te=ar(ma,i);
            ar(ma,i)=ar(cu,i);
            ar(cu,i)=te;
        end
    te=Y(ma);
    Y(ma)=Y(cu);
    Y(cu)=te;
    end
    te=ar(cu,cu);
    for i=cu:no
        for j=cu:no
            ar(i,j)=ar(i,j)/te;
        end
        Y(i)=Y(i)/te;
    end
endfunction
function [ar,Y]=func1(ar,Y,cu,no)
    for i=cu+1:no
        temp=ar(i,cu);
        for j=cu:no
            ar(i,j)=ar(i,j)-ar(cu,j)*temp;
        end
        Y(i,1)=Y(i,1)-Y(cu,1)*temp;
    end
endfunction
function [ar,Y]=gauss1(ar,Y,cu,no)
    Max=0;
    for cu=1:no-1
        [Max]=findmax(no,ar,Max,cu);
        [ar,Y]=swap(cu,Max,ar,Y,no);
        [ar,Y]=func1(ar,Y,cu,no);
    end
endfunction
function [ar,Y,temp_X]=func2(ar,Y,cu,no,temp_X)
    Y1=Y(cu,1);
    if no~=cu then
        for i=no:-1:cu+1
	    disp(i);
            Y1=Y1-ar(cu,i)*temp_X(i,1);
        end
    end
    temp_X(cu,1)=Y1/ar(cu,cu);
endfunction
function [ar,Y,temp_X]=gauss2(ar,Y,cu,no,temp_X)
    for cu=no:-1:1
        [ar,Y,temp_X]=func2(ar,Y,cu,no,temp_X);
	
    end
endfunction
function [temp_X,X,X_k1]=calcSLAU(f1,f2,temp_X,X,X_k1)
    no=2;
    cu=1;
    ar=zeros(2,2);
    Y=zeros(2,1);
    der11=0;
    der12=0;
    der21=0;
    der22=0;
    [der11]=derivative11(X,der11);
    [der12]=derivative12(X,der12);
    [der21]=derivative21(X,der21);
    [der22]=derivative22(X,der22);
    ar(1,1)=der11;
    ar(1,2)=der12;
    ar(2,1)=der21;
    ar(2,2)=der22;
    Y(1,1)=-f1;
    Y(2,1)=-f2;
    [ar,Y]=gauss1(ar,Y,cu,no);
    [ar,Y,temp_X]=gauss2(ar,Y,cu,no,temp_X);
    X_k1(1,1)=X(1,1)+temp_X(1,1);
    X_k1(2,1)=X(2,1)+temp_X(2,1);
endfunction
function [check,d,k]=checkUsl(check,f1,f2,X,X_k1,e,k)
	temp=0;
	if(abs(f1)>abs(f2)) then
	    d(1,1)=abs(f1);
	else 
	    d(1,1)=abs(f2);
	end
    	if (abs(X_k1(1,1)) < 1) then
            d(2,1) = abs(X_k1(1,1) - X(1,1));
    	else
            d(2,1) = abs((X_k1(1,1) - X(1,1))/X_k1(1,1));
	end
    	if (abs(X_k1(2,1)) < 1) then
            temp = abs(X_k1(2,1) - X(2,1));
    	else
            temp = abs((X_k1(2,1) - X(2,1))/X_k1(2,1));
	end
    	if (temp > d(2,1)) then
            d(2,1) = temp;
    	end
	z=zeros(1,3);
	z(1,1)=k;
	z(1,2)=d(1,1);
	z(1,3)=d(2,1);
	disp(z);
	if d(1,1)>e(1,1) then
	    if d(2,1)>e(2,1) then
	        check=0;
	    end
	else 
	    check=1;
	end
endfunction
e=zeros(2,1);
e(1,1)=0.000000001;
e(2,1)=0.000000001;
X=input('');
NIT=input('');
temp_X=zeros(2,1);
X_k1=zeros(2,1);
d=zeros(2,1);
f1=0;
f2=0;
check=0;
k=1;
while 1==1
    [f1]=function1(X,f1);
    [f2]=function2(X,f2);
    [temp_X,X,X_k1]=calcSLAU(f1,f2,temp_X,X,X_k1);
    [check,d,k]=checkUsl(check,f1,f2,X,X_k1,e,k);
    if check==1 then
        break; 
    end
    if k>=NIT then
        disp('IER=2');
	break;
    end
    k=k+1;
    X(1,1)=X_k1(1,1);
    X(2,1)=X_k1(2,1);
end
