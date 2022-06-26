// Adryellen das Graças Santana
// Lucas Oliveira Loura

#include <stdio.h>
#include <stdlib.h>

struct TSalario
{
	double bruto, liquido;
	double aliqINSS, valINSS;
	double baseIR, aliqIR, deducIR, valIR;
};

int main (void)
{
	TSalario *salario, salarioAux;
	int tamSalario = 0, i;
	FILE *arq;

	//arq = fopen("salarioTemp.txt", "r");
	arq = fopen("salario.txt", "r");

	salario = NULL;

	while (fscanf(arq, "%lf", & salarioAux.bruto) != EOF)
	{
		tamSalario++;
		salario = (TSalario *)realloc(salario, sizeof(TSalario) * tamSalario);
		salario[tamSalario - 1] = salarioAux;
	}

	for (i = 0; i < tamSalario; i++) // ALIQUOTA INSS
	{
		if (salario[i].bruto <= 1751.81)
		{
			salario[i].aliqINSS = 8.0;
			salario[i].valINSS = salario[i].bruto * 0.08;
		}
		else if (salario[i].bruto <= 2919.72)
		{
			salario[i].aliqINSS = 9.0;
			salario[i].valINSS = salario[i].bruto * 0.09;
		}
		else if (salario[i].bruto <= 5839.45)
		{
			salario[i].aliqINSS = 11.0;
			salario[i].valINSS = salario[i].bruto * 0.11;
		}	
		else
		{
			salario[i].aliqINSS = 0.0;
			salario[i].valINSS = 0.0;
		}

		salario[i].baseIR = salario[i].bruto - salario[i].valINSS;

		if (salario[i].baseIR <= 1903.98)
		{
			salario[i].aliqIR = 0.0;
			salario[i].deducIR = 0.0;
		}
			
		else if (salario[i].baseIR <=  2826.65)
		{
			salario[i].aliqIR = 7.5;
			salario[i].deducIR = 142.80;
		}
		else if (salario[i].baseIR <=  3751.05)
		{
			salario[i].aliqIR = 15.0;
			salario[i].deducIR = 354.80;
		}
		else if (salario[i].baseIR <=  4664.68)
		{
			salario[i].aliqIR = 22.5;
			salario[i].deducIR = 636.13;
		}

		else
		{
			salario[i].aliqIR = 27.5;
			salario[i].deducIR = 869.36;
		}
		
		salario[i].valIR = (salario[i].bruto - salario[i].valINSS) * (salario[i].aliqIR / 100) - salario[i].deducIR;

		if (salario[i].valIR < 10)
			salario[i].valIR = 0;

		salario[i].liquido = salario[i].bruto - salario[i].valINSS - salario[i].valIR;
	}

	fclose(arq);

	printf("    Bruto   AliqINSS    Val.INSS      Base I.R.    AliqIR        Val.IR       Liquido\n");
	for (i = 0; i < tamSalario; i++)
		printf(" %8.2lf      %5.1lf      %6.2lf      %9.2lf      %4.1lf      %8.2lf      %8.2lf\n", salario[i].bruto, salario[i].aliqINSS, salario[i].valINSS, salario[i].baseIR, salario[i].aliqIR, salario[i].valIR, salario[i].liquido);

	arq = fopen("calculos.txt", "w");

	fprintf(arq, "    Bruto   AliqINSS    Val.INSS      Base I.R.    AliqIR        Val.IR       Liquido\n");
	for (i = 0; i < tamSalario; i++)
		fprintf(arq, " %8.2lf      %5.1lf      %6.2lf      %9.2lf      %4.1lf      %8.2lf      %8.2lf\n", salario[i].bruto, salario[i].aliqINSS, salario[i].valINSS, salario[i].baseIR, salario[i].aliqIR, salario[i].valIR, salario[i].liquido);

	fclose(arq);

	return (0);
}
