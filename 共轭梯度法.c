#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void Hilbrt(int n, double *a, double *b);
void Triangle(int n, double *a, double *b);//���ԽǾ��� 
void Triangle2(int n, int i, double *a, double b);//���������ԽǾ��� 
void Read(); //Read����û��д�á�����Hilbrt���� 
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
	//double A[n*n], b[n];//�洢¼��ķ���
	double A[n],b;
	double x[n], d[n], g[n], t, a, dAd;//�洢����м����� 
	//Hilbrt(n, A, b);//¼����Ծ��� 
	Initialize(n, x);//�ȸ���һ��x0������x������ 
	Grad(n, g, A, b, x);//�Ȱ�x ����g���g0 
	flag = JudgeG(n, g);//�ж�G�ľ����ǲ��ǵ���0�� 
	//��ʼ��d���� �õ�d0 
	for(i = 0; i<n; i++){
		d[i] = -g[i];
	} 
	a = 1;

	while(flag){
		dAd = DTAd(n, d, A); //����׼������ 
		if(fabs(a) > 10E-15){
			t = PramterT(n, dAd, d, g);//����t 
			    //printf("%lf %lf %lf\n",dAd , t, a);
	        NextX(n, d, x, t);//ͨ��t����õ���һ��x
			    //Print(n, x);
	        Grad(n, g, A, b, x);//����gֵ ������g_k+1 
	        flag = JudgeG(n, g);//�ж�g�Ƿ�Ϊ�� 
	        	//Print(n,g); 
	        a = CoefA(n, dAd, d, A, g);//����ϵ��a 
		        //printf("%lf %lf %lf\n",dAd , t, a);
	        Dirct(n, a, d, g);//����һ��d_k���d_k+1 
		}else{
			flag = 0;
		}
	}
	t = PramterT(n, dAd, d, g);//����t 
	NextX(n, d, x, t);
	//n������ g��һ����Ϊ��� 
	Print(n, x);//���gΪ��Ļ�������� 
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

int JudgeG(int n, double *g){//�ж�g�ǲ���0 
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
	}//��ɷ���d�ĸ��� 
}

void Print(int n, double *x){
	int i;
	for(i = 0; i<n; i++){
		printf("%.4lf\n", x[i]);
	}
}

void Hilbrt(int n, double *a, double *b){
	//���Ծ���¼��n��Hilbrt���� 
	int i,j;
	for(i = 0; i<n; i++){
			b[i] = 0.0;
		}
	for (i = 0 ;i < n; i++){//��i�� ��j�еľ��� 
		for(j = 0; j<n; j++){
			a[i*n + j] = 1.0 / (i+j+1);
			b[i] += a[i*n + j];
		}
	} 
}

void Triangle(int n, double *a, double *b){
	//���Ծ���¼�����ԽǾ��� 
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
}//���������ԽǾ��� 
 
