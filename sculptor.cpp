#include "sculptor.hpp"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cmath>

using namespace std;

Sculptor::Sculptor(int _nx, int _ny, int _nz) // Construtor da classe
{
    //Inicializando as dimensoes	
    nx = _nx;
    ny = _ny;
    nz = _nz;
    
    //Inicializando as cores e o parametro alpha  
    r = 0.0;
    g = 0.0;
    b = 0.0;
    a = 0.0;
    
	//Incializando a Alocacao dinamica de memoria (ponteiro para ponteiro para ponteiro para voxel) Matriz 3D
    v = new Voxel **[_nx];
    for (int i = 0; i < _nx; i++)
    {
        v[i] = new Voxel *[_ny];
        for (int j = 0; j < _ny; j++)
        {
            v[i][j] = new Voxel[_nz];
            for (int k = 0; k < _nz; k++)
            {
                v[i][j][k].r = 0.0;
                v[i][j][k].g = 0.0;
                v[i][j][k].b = 0.0;
                v[i][j][k].a = 0.0;
                v[i][j][k].isOn = false;
            }
        }
    }
}

Sculptor::~Sculptor() // Destrutor da classe
{
	// Liberando a mememoria alocada
    for (int i = 0; i < nx; i++)
    {
        for (int j = 0; j < ny; j++)
        {
            delete[] v[i][j];
        }
        delete[] v[i];
    }
    delete[] v;
    
  // Zerando os demais parametros
	nx = 0;
	ny = 0;
	nz = 0;
    r = 0;
	g = 0;
	b = 0;
	a = 0;
}

void Sculptor::setColor(float nr, float ng, float nb, float nalpha) // Definindo a cor atual
{
    r = nr;
    g = ng;
    b = nb;
    a = nalpha;
}

void Sculptor::putVoxel(int x, int y, int z) // Ativa o voxel na posição (x,y,z) (fazendo isOn = true) e atribui ao mesmo a cor atual de desenho
{
	if (x>=0 && x<nx && y>=0 && y<ny && z>=0 && z<nz) // Testa se a posição é valida
	{
    	v[x][y][z].isOn = true;
    	v[x][y][z].r = r;
    	v[x][y][z].g = g;
    	v[x][y][z].b = b;
    	v[x][y][z].a = a;
	}
}

void Sculptor::cutVoxel(int x, int y, int z) // Desabilita o voxel
{
	if (x>=0 && x<nx && y>=0 && y<ny && z>=0 && z<nz) // Testa se a posição é valida
	{
    	v[x][y][z].isOn = false;
	}
}

void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1) // Habilita os voxels nesse intervalo, formando um paralelepipedo (uma "caixa")
{
    for (int i = x0; i < x1; i++)
    {
        for (int j = y0; j < y1; j++)
        {
            for (int k = z0; k < z1; k++)
            {
                putVoxel(i, j, k);
            }
        }
    }
}

void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1) // Desabilita o paralelepipedo (uma "caixa")
{

    for (int i = x0; i < x1; i++)
    {
        for (int j = y0; j < y1; j++)
        {
            for (int k = z0; k < z1; k++)
            {
                cutVoxel(i, j, k);
            }
        }
    }
}

void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius) // Habilita os voxels que satisfazem a equação da esfera
{
	// Equacao da esfera  (x - a)² + (y - b)² + (z - c)² = r²
    for(int i=0; i<nx; i++)
	{
        for(int j=0; j<ny; j++)
		{
            for(int k=0; k<nz; k++)
			{
                if(pow(i - xcenter, 2)+pow(j - ycenter, 2)+pow(k - zcenter, 2)<= pow(radius, 2))
				{
                    putVoxel(i,j,k);
                }
            }
        }
    }
}

void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius) // Desabilita os voxels que satisfazem a equação da esfera
{
    for(int x=0; x<nx; x++)
	{
        for(int y=0; y<ny; y++)
		{
            for(int z=0; z<nz; z++)
			{
                if(pow(x - xcenter, 2)+pow(y - ycenter, 2)+pow(z - zcenter, 2)<= pow(radius, 2))
				{
                    cutVoxel(x,y,z);
                }
            }
        }
    }
}

void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx,int ry,int rz) // Habilita os voxels que satisfazem a equação do elipsoide
{
	// Equacao da elipsoide : [(x - i)/a]² + [(y - j)/b]² + [(z - k)/c]² = 1
    for(int i = xcenter - rx; i < xcenter + rx; i++)
	{
        for(int j = ycenter - ry; j < ycenter + ry; j++)
		{
            for(int k = zcenter - rz; k < zcenter + rz; k++)
			{
                if(pow(i - xcenter, 2)/pow(rx, 2) + pow(j - ycenter, 2)/pow(ry, 2) + pow(k - zcenter, 2)/pow(rz, 2) < 1)
				{
                    putVoxel(i, j, k);
                }
            }
        }
    }
}

void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx,int ry,int rz) // Desabilita os voxels que satisfazem a equação do elipsoide
{
    for(int x = xcenter - rx; x < xcenter + rx; x++)
	{
        for(int y = ycenter - ry; y < ycenter + ry; y++)
		{
            for(int z = zcenter - rz; z < zcenter + rz; z++)
			{
                if(pow(z - zcenter, 2)/pow(rz, 2) + pow(y - ycenter, 2)/pow(ry, 2) + pow(x - xcenter, 2)/pow(rx, 2) < 1)
				{
                    cutVoxel(x, y, z);
                }
            }
        }
    }
}

void Sculptor::writeOFF(char* filename) // Grava a escultura no formato OFF no arquivo filename
{
    
    ofstream arquivo(filename); // Conectando o fluxo de saída com o arquivo filename
    fixed(arquivo);
    
    //Inciando o fluxo
    if (!arquivo.is_open()) // Verifica se o fluxo foi aberto
    {
        cout << "Nao foi possivel abrir o arquivo!!!" << endl;
        exit(1);
    }
    
    //Contabilizando a quantidade de voxels ativos (isto é, .isOn == true)
    int total = 0, i, j, k;
    for (i = 0; i < nx; i++)
    {
        for (j = 0; j < ny; j++)
        {
            for (k = 0; k < nz; k++)
            {
                if (v[i][j][k].isOn)
                {
                    total++;
                }
            }
        }
    }
    
    // Escrevendo no arquivo .OFF 
    arquivo << "OFF" << endl; // Todo arquivo .OFF inicia com os dizeres "OFF"
    arquivo << 8 * total << " " << 6 * total << " 0" << endl; // Total de Vertices, faces e arestas (este ultimo é sempre 0)

	// Escrevendo a lista de vértices
    for (i = 0; i < nx; i++)
    {
        for (j = 0; j < ny; j++)
        {
            for (k = 0; k < nz; k++)
            {
                if (v[i][j][k].isOn)
                {
                    arquivo << i - 0.5 << " " << j + 0.5 << " " << k - 0.5 << endl;
                    arquivo << i - 0.5 << " " << j - 0.5 << " " << k - 0.5 << endl;
                    arquivo << i + 0.5 << " " << j - 0.5 << " " << k - 0.5 << endl;
                    arquivo << i + 0.5 << " " << j + 0.5 << " " << k - 0.5 << endl;
                    arquivo << i - 0.5 << " " << j + 0.5 << " " << k + 0.5 << endl;
                    arquivo << i - 0.5 << " " << j - 0.5 << " " << k + 0.5 << endl;
                    arquivo << i + 0.5 << " " << j - 0.5 << " " << k + 0.5 << endl;
                    arquivo << i + 0.5 << " " << j + 0.5 << " " << k + 0.5 << endl;
                }
            }
        }
    }
    
    // Escrevendo a lista de faces e os parametros rbga
    int cont = 0;
    for (i = 0; i < nx; i++)
    {
        for (j = 0; j < ny; j++)
        {
            for (k = 0; k < nz; k++)
            {
                if (v[i][j][k].isOn)
                {
                	// Cada linha representa um poligono no espaço 3D!
                	arquivo << "4 " << cont * 8 + 0 << " " << cont * 8 + 3 << " " << cont * 8 + 2 << " " << cont * 8 + 1 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << endl;
                    arquivo << "4 " << cont * 8 + 4 << " " << cont * 8 + 5 << " " << cont * 8 + 6 << " " << cont * 8 + 7 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << endl;
                    arquivo << "4 " << cont * 8 + 0 << " " << cont * 8 + 1 << " " << cont * 8 + 5 << " " << cont * 8 + 4 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << endl;
                    arquivo << "4 " << cont * 8 + 0 << " " << cont * 8 + 4 << " " << cont * 8 + 7 << " " << cont * 8 + 3 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << endl;
                    arquivo << "4 " << cont * 8 + 3 << " " << cont * 8 + 7 << " " << cont * 8 + 6 << " " << cont * 8 + 2 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << endl;
                    arquivo << "4 " << cont * 8 + 1 << " " << cont * 8 + 2 << " " << cont * 8 + 6 << " " << cont * 8 + 5 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << endl;
                    cont++;
                }
            }
        }
    }
    
    arquivo.close(); // Fechando o arquivo
}
