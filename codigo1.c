#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//***************************Tarefa feita na sala de aula: Resolver o problema de contorno y" = y' + 2y + cos(x) com as condições iniciais especificadas no pdf dado**********************************************************************************************
#define M 2
#define N 2
#define NP 10
FILE *arquivo;


typedef double (*sistfunc)();

double f(double y[], double t)
{
	return y[1];
}

double f2(double y[], double t)
{
	return y[1] + 2*y[0];
}
double f1(double y[], double t)
{
	return f2(y,t) + cos(t);
}
double rk(sistfunc func[], double y[], double t, double h)
{
	double k1[N], k2[N], k3[N], k4[N], yp[N];
	int i;
	
	for( i=0; i<N; i++) k1[i] = func[i](y,t);
	for( i=0; i<N; i++) yp[i]=y[i]+(k1[i]*(h/2));

	
	for( i=0; i<N; i++) k2[i] = func[i](yp,t + (h/2));	
	for( i=0; i<N; i++) yp[i]=y[i]+(k2[i]*(h/2));
	
	for( i=0; i<N; i++) k3[i] = func[i](yp,t + (h/2));
	for( i=0; i<N; i++) yp[i] = y[i]+(k3[i]*h);
	
	for( i=0; i<N; i++) k4[i] = func[i](yp,t + h);
	
	for( i=0; i<N; i++) y[i] = y[i] + (h/6.0)*(k1[i] + 2*k2[i] + 2*k3[i] + k4[i]);
	
	
	return y[0];
}

void main (int argc, char **argv)
{
	double a,b,h, y[M]={-0.3, 0}, y2[M]={0,1},ye1[NP+1],ye2[NP+1], yen[NP+1], yex[NP+1], t; //*condição inicial y[M]={-0.3, 0}
	sistfunc equacoes[N]={f,f1}, equacoes2[N]={f,f2}; //primeira e a completa
        arquivo =  fopen(argv[1], "w");
	int i, j;
	a=0;
	b=M_PI/2;


	h=(b-a)/NP;
	t=a;
	ye1[0]=y[0];
	ye2[0]=y2[0];
	i=1;
	
	while(t<b)
	{
		ye1[i]=rk(equacoes,y,t,h);
		ye2[i]=rk(equacoes2,y2,t,h);

		t+=h;
		i++;
	}
		
	t = a;

	for(i=0;i<=NP;i++)
	{
		yex[i] = ye1[i] + ( ( -0.1 -ye1[NP]) / ye2[NP] )*ye2[i];
		printf("%.2f\t%f\t%f\t%f\n", t, ye1[i], ye2[i], yex[i]);
		fprintf(arquivo,"%lf\t%lf\t%lf\t%lf\n", t, ye1[i], ye2[i], yex[i]);

		
		t+=h;
	}
	fclose(arquivo);
		
}	
