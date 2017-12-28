funcprot(0);
function []=checkUslovie(N,a)
    num=0;
    summ=0;
    for i=1:N
        num=abs(a(i,i));
        for j=1:N
            if(i~=j) then
                summ=summ+abs(a(i,j));
            end
        end
        if(num<summ) then
            disp('Условие диагонального преобладания не выполнено!');
            abort;
        end
        summ=0;
    end
endfunction
function[x]=findX(N,method,y,a,tempX)
    if(method==1) then
        for i=1:N
            x(i,1)=y(i,1);
            for j=1:N
                if(i~=j) then
                    x(i,1)=x(i,1)-a(i,j)*tempX(j,1);
                end
            end
            x(i,1)=x(i,1)/a(i,i);
        end
    end
    if(method==2) then
        for i=1:N
            x(i,1)=y(i,1);
            for j=1:i
                if(i~=j) then
                    x(i,1)=x(i,1)-a(i,j)*x(j,1);
                end
            end
            for j=i:N
                if(i~=j) then
                    x(i,1)=x(i,1)-a(i,j)*tempX(j,1);
                end 
            end           
            x(i,1)=x(i,1)/a(i,i);
        end        
    end
endfunction
function[iter,x,tempX]=func(E,N,y,a,method,iter,x,tempX)
    Max=0;
    while 1
        [x]=findX(N,method,y,a,tempX);
        iter=iter+1;
        Max=abs(x(1,1)-tempX(1,1));
        for i=2:N
            if(Max<abs(x(i,1)-tempX(i,1))) then
                Max=abs(x(i,1)-tempX(i,1));
            end
        end
        if(Max<E) then
            return
        end
        for i=1:N
            tempX(i,1)=x(i,1);
        end
    end
endfunction
N=input('N=');
E=input('E=');
x=zeros(N,1);
iter=0;
disp('Ввод матрицы A');
a=input('');   
disp('Ввод матрицы Y');
y=input('');
if(size(a,1)~=N) then
    abort;
    elseif (size(a,2)~=N) then
        abort;
        elseif (size(y)~=N)
            abort;
end
checkUslovie(N,a);
tempX=zeros(N,1)
z=[a y];
disp('');
disp('Система:');
disp(z);
[iter,x,tempX]=func(E,N,y,a,1,iter,x,tempX);
disp('');
disp('Метод Якоби:');
disp('Решение:');
disp(x);
disp('Итераций:');
disp(iter);
for i=1:N
    x(i,1)=0;
    tempX(i,1)=0;
    F(i,1)=0;
end
iter=0;
d=0;
[iter,x,tempX]=func(E,N,y,a,2,iter,x,tempX);
disp('');
disp('Метод Зейделя:');
disp('Решение:');
disp(x);
disp('Итераций:');
disp(iter);
