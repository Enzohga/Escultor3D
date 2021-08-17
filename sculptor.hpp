#ifndef SCULPTOR_HPP //Diretiva de compilação condicional 
#define SCULPTOR_HPP

struct Voxel 
{
  float r,g,b; // Cores
  float a;    // Transparencia
  bool isOn; // Incluso ou não
};

class Sculptor 
{
protected:
  Voxel ***v;   // Matriz 3D 
  int nx,ny,nz; // Dimensoes
  float r,g,b,a; //  Cor e parametro alpha (transparencia)
public:
  Sculptor(int _nx, int _ny, int _nz); // Construtor
  ~Sculptor(); // Destrutor
  void setColor(float nr, float ng, float nb, float nalpha); // Ativar cores 
  void putVoxel(int x, int y, int z); // Habilita voxel na posição determinada
  void cutVoxel(int x, int y, int z); // Desabilita voxel
  void putBox(int x0, int x1, int y0, int y1, int z0, int z1); // Habilita os voxels nesse intervalo, formando assim um paralelepipedo (uma "caixa")
  void cutBox(int x0, int x1, int y0, int y1, int z0, int z1); // Desabilita os voxels do paralelepipedo (uma "caixa")
  void putSphere(int xcenter, int ycenter, int zcenter, int radius); // Habilita os voxels que satisfazem a equação da esfera
  void cutSphere(int xcenter, int ycenter, int zcenter, int radius);// Desabilita os voxels que satisfazem a equação da esfera
  void putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz); // Habilita os voxels que satisfazem a equação do elipsoide
  void cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz); // Desabilita os voxels que satisfazem a equação do elipsoide
  void writeOFF(char* filename); // Grava a escultura no formato OFF no arquivo filename
};

#endif // SCULPTOR_HPP

