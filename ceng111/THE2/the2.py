row_list=eval(input())
row_list_row=row_list[:]
a=row_list_row[0][:]
b=row_list_row[1][:]
c=row_list_row[2][:]
d=row_list_row[3][:]
row_list_abs_y=[(a[0],abs(a[1])),(b[0],abs(b[1])),(c[0],abs(c[1])),(d[0],abs(d[1]))]
row_list_abs_y_not_sorted=row_list_abs_y[:]
row_list_abs_y.sort()
q=row_list_abs_y[0]
w=row_list_abs_y[1]
e=row_list_abs_y[2]
r=row_list_abs_y[3]
x_list=[q[0],w[0],e[0],r[0]]
y_list=[q[1],w[1],e[1],r[1]]
x_sol , y_sol , x_orta1 , y_orta1 = q[0] , q[1] , w[0] , w[1]
y_orta1_yukarda = False
y_orta1_asagida = False
y_orta2_yukarda = False
y_orta2_asagida = False
if e[0]==r[0]:
    x_sag , y_sag , x_orta2 , y_orta2 = e[0] , e[1] , r[0] , r[1]
else:
    x_sag , y_sag , x_orta2 , y_orta2 = r[0] , r[1] , e[0] , e[1]
if  x_orta1==x_sol:
    if y_orta1>=y_sol:
        y_orta1_yukarda = True
    else:
        y_orta1_asagida = True
elif (y_orta1-y_sol)/(x_orta1-x_sol)>(y_sag-y_sol)/(x_sag-x_sol):
    y_orta1_yukarda = True
else:
    y_orta1_asagida = True
if  (y_orta2-y_sol)/(x_orta2-x_sol)>(y_sag-y_sol)/(x_sag-x_sol):
    y_orta2_yukarda = True
else:
    y_orta2_asagida = True
x_0,y_0=x_sol,y_sol
x_1,y_1=x_orta1,y_orta1
x_2,y_2=x_orta2,y_orta2
x_3,y_3=x_sag,y_sag
x__0 , y__0 = row_list_abs_y_not_sorted[0][0] , row_list_abs_y_not_sorted[0][1]
x__1 , y__1 = row_list_abs_y_not_sorted[1][0] , row_list_abs_y_not_sorted[1][1]
x__2 , y__2 = row_list_abs_y_not_sorted[2][0] , row_list_abs_y_not_sorted[2][1]
x__3 , y__3 = row_list_abs_y_not_sorted[3][0] , row_list_abs_y_not_sorted[3][1]
#Bi nokta üstte bi nokta altta yani 1.case
if (y_orta1_asagida and y_orta2_yukarda):
    alan = ((((y_sol + y_sag)/2)*(x_sag - x_sol))-(1 / 2 * abs(((x_1 * y_0) + (x_3 * y_1) + (x_0 * y_3)) - ((x_0 * y_1) + (x_1 * y_3) + (x_3 * y_0)))))
if (y_orta1_yukarda and y_orta2_asagida):
    alan = ((((y_sol + y_sag)/2)*(x_sag - x_sol))-(1 / 2 * abs(((x_2 * y_0) + (x_3 * y_2) + (x_0 * y_3)) - ((x_0 * y_2) + (x_2 * y_3) + (x_3 * y_0)))))
#İki nokta da üstte
if y_orta2_yukarda and y_orta1_yukarda:
    #yamuk+üçgen 3.case
    if (x_sol==x_orta1 and y_orta1==y_orta2) and ((row_list_abs_y_not_sorted[0]==(x_sol,y_sol) and row_list_abs_y_not_sorted[2]==(x_sag,y_sag)) or (row_list_abs_y_not_sorted[1]==(x_sol,y_sol) and row_list_abs_y_not_sorted[3]==(x_sag,y_sag)) or (row_list_abs_y_not_sorted[2]==(x_sol,y_sol) and row_list_abs_y_not_sorted[0]==(x_sag,y_sag)) or (row_list_abs_y_not_sorted[3]==(x_sol,y_sol) and row_list_abs_y_not_sorted[1]==(x_sag,y_sag))):
        alan = (((y_sol+y_sag)/2)*(x_sag-x_sol)) + (1 / 2 * abs(((x_2 * y_0) + (x_3 * y_2) + (x_0 * y_3)) - ((x_0 * y_2) + (x_2 * y_3) + (x_3 * y_0))))
    elif (x_sag==x_orta2 and y_orta1==y_orta2) and ((row_list_abs_y_not_sorted[0]==(x_sol,y_sol) and row_list_abs_y_not_sorted[2]==(x_sag,y_sag)) or (row_list_abs_y_not_sorted[1]==(x_sol,y_sol) and row_list_abs_y_not_sorted[3]==(x_sag,y_sag)) or (row_list_abs_y_not_sorted[2]==(x_sol,y_sol) and row_list_abs_y_not_sorted[0]==(x_sag,y_sag)) or (row_list_abs_y_not_sorted[3]==(x_sol,y_sol) and row_list_abs_y_not_sorted[1]==(x_sag,y_sag))):
        alan = (((y_sol+y_sag)/2)*(x_sag-x_sol)) + (1 / 2 * abs(((x_1 * y_0) + (x_3 * y_1) + (x_0 * y_3)) - ((x_0 * y_1) + (x_1 * y_3) + (x_3 * y_0))))
    elif (x_sol==x_orta1 and y_orta2==y_sag) and ((row_list_abs_y_not_sorted[0]==(x_sol,y_sol) and row_list_abs_y_not_sorted[2]==(x_sag,y_sag)) or (row_list_abs_y_not_sorted[1]==(x_sol,y_sol) and row_list_abs_y_not_sorted[3]==(x_sag,y_sag)) or (row_list_abs_y_not_sorted[2]==(x_sol,y_sol) and row_list_abs_y_not_sorted[0]==(x_sag,y_sag)) or (row_list_abs_y_not_sorted[3]==(x_sol,y_sol) and row_list_abs_y_not_sorted[1]==(x_sag,y_sag))):
        alan = (((y_sol+y_sag)/2)*(x_sag-x_sol)) + (1 / 2 * abs(((x_2 * y_0) + (x_3 * y_2) + (x_0 * y_3)) - ((x_0 * y_2) + (x_2 * y_3) + (x_3 * y_0))))
    elif (x_sag==x_orta2 and y_sol==y_orta1) and ((row_list_abs_y_not_sorted[0]==(x_sol,y_sol) and row_list_abs_y_not_sorted[2]==(x_sag,y_sag)) or (row_list_abs_y_not_sorted[1]==(x_sol,y_sol) and row_list_abs_y_not_sorted[3]==(x_sag,y_sag)) or (row_list_abs_y_not_sorted[2]==(x_sol,y_sol) and row_list_abs_y_not_sorted[0]==(x_sag,y_sag)) or (row_list_abs_y_not_sorted[3]==(x_sol,y_sol) and row_list_abs_y_not_sorted[1]==(x_sag,y_sag))):
        alan = (((y_sol+y_sag)/2)*(x_sag-x_sol)) + (1 / 2 * abs(((x_1 * y_0) + (x_3 * y_1) + (x_0 * y_3)) - ((x_0 * y_1) + (x_1 * y_3) + (x_3 * y_0))))
    elif y_orta1 > y_orta2:
        if (row_list_abs_y_not_sorted[0]==(x_sol,y_sol) and row_list_abs_y_not_sorted[2]==(x_sag,y_sag)) or (row_list_abs_y_not_sorted[1]==(x_sol,y_sol) and row_list_abs_y_not_sorted[3]==(x_sag,y_sag)) or (row_list_abs_y_not_sorted[2]==(x_sol,y_sol) and row_list_abs_y_not_sorted[0]==(x_sag,y_sag)) or (row_list_abs_y_not_sorted[3]==(x_sol,y_sol) and row_list_abs_y_not_sorted[1]==(x_sag,y_sag)):
            alan = (((y_sol+y_sag)/2)*(x_sag-x_sol)) + (1 / 2 * abs(((x_2 * y_0) + (x_3 * y_2) + (x_0 * y_3)) - ((x_0 * y_2) + (x_2 * y_3) + (x_3 * y_0))))
        else:  # altta kalan yamuk 2 ve 6.case
            alan = (((y_sol + y_sag) / 2) * (x_sag - x_sol))
    elif y_orta2>=y_orta1:
        if (row_list_abs_y_not_sorted[0]==(x_sol,y_sol) and row_list_abs_y_not_sorted[2]==(x_sag,y_sag)) or (row_list_abs_y_not_sorted[1]==(x_sol,y_sol) and row_list_abs_y_not_sorted[3]==(x_sag,y_sag)) or (row_list_abs_y_not_sorted[2]==(x_sol,y_sol) and row_list_abs_y_not_sorted[0]==(x_sag,y_sag)) or (row_list_abs_y_not_sorted[3]==(x_sol,y_sol) and row_list_abs_y_not_sorted[1]==(x_sag,y_sag)):
            alan = (((y_sol+y_sag)/2)*(x_sag-x_sol)) + (1 / 2 * abs(((x_1 * y_0) + (x_3 * y_1) + (x_0 * y_3)) - ((x_0 * y_1) + (x_1 * y_3) + (x_3 * y_0))))
        else:  # altta kalan yamuk 2 ve 6.case
            alan = (((y_sol + y_sag) / 2) * (x_sag - x_sol))
#iki nokta da altta
if y_orta1_asagida and y_orta2_asagida:
    #4.case yamuk - büyük üçgen
    if y_orta1 > y_orta2:
        if (row_list_abs_y_not_sorted[0]==(x_sol,y_sol) and row_list_abs_y_not_sorted[2]==(x_sag,y_sag)) or (row_list_abs_y_not_sorted[1]==(x_sol,y_sol) and row_list_abs_y_not_sorted[3]==(x_sag,y_sag)) or (row_list_abs_y_not_sorted[2]==(x_sol,y_sol) and row_list_abs_y_not_sorted[0]==(x_sag,y_sag)) or (row_list_abs_y_not_sorted[3]==(x_sol,y_sol) and row_list_abs_y_not_sorted[1]==(x_sag,y_sag)):
            alan = (((y_sol+y_sag)/2)*(x_sag-x_sol)) - (1 / 2 * abs(((x_2 * y_0) + (x_3 * y_2) + (x_0 * y_3)) - ((x_0 * y_2) + (x_2 * y_3) + (x_3 * y_0))))
        else:  # 5 ve 7.case yamuk-dörtgen
            alan = (((y_sol + y_sag) / 2) * (x_sag - x_sol)) - (1/2*abs(((x__0*y__1)+(x__1*y__2)+(x__2*y__3)+(x__3*y__0))-((x__1*y__0)+(x__2*y__1)+(x__3*y__2)+(x__0*y__3))))
    elif y_orta2 >= y_orta1:
        if (row_list_abs_y_not_sorted[0]==(x_sol,y_sol) and row_list_abs_y_not_sorted[2]==(x_sag,y_sag)) or (row_list_abs_y_not_sorted[1]==(x_sol,y_sol) and row_list_abs_y_not_sorted[3]==(x_sag,y_sag)) or (row_list_abs_y_not_sorted[2]==(x_sol,y_sol) and row_list_abs_y_not_sorted[0]==(x_sag,y_sag)) or (row_list_abs_y_not_sorted[3]==(x_sol,y_sol) and row_list_abs_y_not_sorted[1]==(x_sag,y_sag)):
            alan = (((y_sol+y_sag)/2)*(x_sag-x_sol)) - (1 / 2 * abs(((x_1 * y_0) + (x_3 * y_1) + (x_0 * y_3)) - ((x_0 * y_1) + (x_1 * y_3) + (x_3 * y_0))))
        else:  # 5 ve 7.case yamuk-dörtgen
            alan = (((y_sol + y_sag) / 2) * (x_sag - x_sol)) - (1/2*abs(((x__0*y__1)+(x__1*y__2)+(x__2*y__3)+(x__3*y__0))-((x__1*y__0)+(x__2*y__1)+(x__3*y__2)+(x__0*y__3))))
print("%.2f" % alan)