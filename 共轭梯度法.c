#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void Hilbrt(int n, double *a, double *b);
void Triangle(int n, double *a, double *b);//三对角矩阵 
void Triangle2(int n, int i, double *a, double b);//改良的三对角矩阵 
void Read(); //Read函数没有写好。先以Hilbrt代替 
void Print(int n, double *x);
void Initialize(int n, double *x);
void Grad(int n, double *g, double *A, double *b, double *x); 
int JudgeG(int n, double *g); 
void Dirct(int n,double a, double *d, double *g); 
double PramterT(int n, double dAd, double *d, double *g);
double CoefA(int n, double dAd, double *d, double *A, double *g);
double DTAd(int n, double *d, double *A); 
void NextX(int n, double *d, double *x, double t);

int main(){
	int i,n;
	int flag;
	scanf("%d", &n);
	//double A[n*n], b[n];//存储录入的方程
	double A[n],b;
	double x[n], d[n], g[n], t, a, dAd;//存储解和中间向量 
	//Hilbrt(n, A, b);//录入测试矩阵 
	Initialize(n, x);//先给出一组x0，代入x向量中 
	Grad(n, g, A, b, x);//先把x 代入g求出g0 
	flag = JudgeG(n, g);//判断G的距离是不是等于0了 
	//初始化d向量 得到d0 
	for(i = 0; i<n; i++){
		d[i] = -g[i];
	} 
	a = 1;

	while(flag){
		dAd = DTAd(n, d, A); //计算准备工作 
		if(fabs(a) > 10E-15){
			t = PramterT(n, dAd, d, g);//计算t 
			    //printf("%lf %lf %lf\n",dAd , t, a);
	        NextX(n, d, x, t);//通过t计算得到下一组x
			    //Print(n, x);
	        Grad(n, g, A, b, x);//计算g值 现在是g_k+1 
	        flag = JudgeG(n, g);//判断g是否为零 
	        	//Print(n,g); 
	        a = CoefA(n, dAd, d, A, g);//计算系数a 
		        //printf("%lf %lf %lf\n",dAd , t, a);
	        Dirct(n, a, d, g);//根据一组d_k算出d_k+1 
		}else{
			flag = 0;
		}
	}
	t = PramterT(n, dAd, d, g);//计算t 
	NextX(n, d, x, t);
	//n次以内 g是一定会为零的 
	Print(n, x);//如果g为零的话，输出答案 
	return 0;
} 

void Initialize(int n, double *x){
	int i;
	x[0] = 1.0;
	for(i = 1;i<n; i++){
		x[i] = 0.0;
	}
} 

void Grad(int n, double *g, double *A, double *b, double *x){
	int i,j;
	for(i = 0; i<n; i++){
		//Triangle2(n,i,a,b);
		g[i] = 0; 
		for(j = 0; j<n; j++){
			g[i] += A[i*n + j] * x[j];
			//g[i] += A[j] * x[j];
		}
		g[i] -= b[i];
	}
}

int JudgeG(int n, double *g){//判断g是不是0 
	int i = 0;
	double sum = 0.0;
	for(i = 0; i<n; i++){
		sum += g[i]*g[i];
	}
	//printf("\n",sum);
	if(fabs(sum) > 1.0E-15){
		return 1;
	}else{
		return 0;
	}
}

double DTAd(int n, double *d, double *A){
	double dAd = 0.0;
	double dA[n]; 
	int i,j; 
	for(i = 0; i< n; i++){
		dA[i] = 0;
		for(j = 0; j<n; j++){
			dA[i] += d[j] * A[i*n + j];
		}
	} 
	for(i = 0; i<n; i++){
		dAd += dA[i] * d[i]; 
	}
	return dAd;
}

double PramterT(int n, double dAd, double *d, double *g){
	double t = 0.0;
	int i,j;
	for(i = 0; i< n; i++){
		t -= g[i] * d[i];
	}
	t /= dAd;
	return t;
}

double CoefA(int n, double dAd, double *d, double *A, double *g){
	double a = 0.0;
	double dA[n]; 
	int i,j; 
	for(i = 0; i< n; i++){
		dA[i] = 0;
		for(j = 0; j<n; j++){
			dA[i] += d[j] * A[i*n + j];
		}
	} 
	for(i = 0; i<n; i++){
		a += dA[i] * g[i]; 
	}
	a /= dAd;
	return a;
}

void NextX(int n, double *d, double *x, double t){
	int i;
	for(i = 0; i<n; i++){
		x[i] += t *d[i];
	}
}

void Dirct(int n,double a, double *d, double *g){
	int i;
	for(i = 0; i<n; i++){
		d[i] = -g[i] + a* d[i];
	}//完成方向d的更新 
}

void Print(int n, double *x){
	int i;
	for(i = 0; i<n; i++){
		printf("%.4lf\n", x[i]);
	}
}

void Hilbrt(int n, double *a, double *b){
	//测试矩阵：录入n阶Hilbrt矩阵 
	int i,j;
	for(i = 0; i<n; i++){
			b[i] = 0.0;
		}
	for (i = 0 ;i < n; i++){//第i行 第j列的矩阵 
		for(j = 0; j<n; j++){
			a[i*n + j] = 1.0 / (i+j+1);
			b[i] += a[i*n + j];
		}
	} 
}

void Triangle(int n, double *a, double *b){
	//测试矩阵：录入三对角矩阵 
	int i = 0;
	for(i = 0; i< n*n; i++){
	    a[i] = 0.0;
	}
	for(i = 0; i< n; i++){
	    a[i*n + i] = 10.0;
	    if(i>0){
			a[i*n + i - 1] = 1.0;
		}
	    if(i < n-1){
	    	a[i*n + i + 1] = 1.0;
		}
	}
	b[0] = 11;
	for(i = 1; i<n-1; i++){
		b[i] = 12;
	} 
	b[n-1] = 11;
} 
void Triangle2(int n, int i, double *a, double b){
	a[i] = 10;
	b[i] = 12;
	if(i > 0){
		a[i - 1] = 1;
	}
	if(i < n-1){
		a[i + 1] = 1;
	}
	if(i == 0 || i == n-1){
		b = 11;
	}
}//改良的三对角矩阵 
 
