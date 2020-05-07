#include "GameState.h"

#include <string>
#include <iostream>
#include <iomanip>
#include <math.h>

GameState::GameState()
{
}


GameState::~GameState()
{

}

void GameState::Create(int p_gridx, int p_gridy)
{
	//setting grid size
	

	totalvolume = 0;
	m_numberofcells[0] = p_gridx;
	m_numberofcells[1] = p_gridy;

	//creating cells
	m_cells = new Cell*[p_gridx];

	for(int i = 0; i < m_numberofcells[0]; i++)
	{
		m_cells[i] = new Cell[p_gridy];
	}

	//positioning cells
	for (int i = 0; i < m_numberofcells[0]; i++)
	{
		for (int j = 0; j < m_numberofcells[1]; j++)
		{
			m_cells[i][j].x = i * m_cellsize;
			m_cells[i][j].y = j * m_cellsize;
			m_cells[i][j].w = m_cellsize;
			m_cells[i][j].h = m_cellsize;
		}
	}

	//giving cells neighbour contact (initialization)
	for (int i = 0; i < m_numberofcells[0]; i++)
	{
		for (int j = 0; j < m_numberofcells[1]; j++)
			{
				Cell* tempcells[4];
				if (i == 0)
				{
					tempcells[3] = nullptr;
				}
				else 
				{
					tempcells[3] = &m_cells[i - 1][j];
				}

				if (i == m_numberofcells[0]-1)
				{
					tempcells[1] = nullptr;
				}
				else
				{
					tempcells[1] = &m_cells[i + 1][j];
				}

				if (j == 0)
				{
					tempcells[0] = nullptr;
				}
				else
				{
					tempcells[0] = &m_cells[i][j-1];
				}

				if (j == m_numberofcells[1] - 1)
				{
					tempcells[2] = nullptr;
				}
				else
				{
					tempcells[2] = &m_cells[i][j+1];
				}

				m_cells[i][j].Initialize(tempcells[0], tempcells[1], tempcells[2], tempcells[3]);
				
			}

	}
}

void GameState::Initialize() 
{
	Create(100, 50);
}

void GameState::Update(InputManager& p_InputManager, double deltatime) 
{
	
	totalvolume = 0;


	for (int i = 0; i < m_numberofcells[1]; i++)
	{
		for (int j = 0; j < m_numberofcells[0]; j++)
		{

			m_cells[j][i].AirPressure();

		}
	}
	
	/*for (int i = 0; i < m_numberofcells[1]; i++)
	{
		for (int j = 0; j < m_numberofcells[0]; j++)
		{
			
			
			m_cells[j][i].AirPressureForce(deltatime,2,2);
			
			
		}
	}*/

	


	if (p_InputManager.m_KeyDown[Key_W])
	{
		m_yacc = 2;

	}
	else if (p_InputManager.m_KeyDown[Key_S])
	{
		m_yacc = -2;

	}
	else
	{
		m_yacc = 0;
	}
	
	if (p_InputManager.m_KeyDown[Key_D])
	{
		m_xacc = 2;

	}
	else if (p_InputManager.m_KeyDown[Key_A])
	{
		m_xacc = -2;

	}
	else
	{
		m_xacc = 0;
	}


	for (int i = 0; i < m_numberofcells[1]; i++)
	{
		for (int j = 0; j < m_numberofcells[0]; j++)
		{
			if (i == (int)(p_InputManager.m_MousePosition.m_y / m_cellsize))
			{
				
				if (j == (int)(p_InputManager.m_MousePosition.m_x / m_cellsize))
				{
					/*system("CLS");
					printf("%f", (p_InputManager.m_MousePosition.m_y / m_cellsize));
					printf("%f", (p_InputManager.m_MousePosition.m_x / m_cellsize));*/

				}

			}
			
			if (p_InputManager.m_MouseDown)
			{
				double t_dx = j * m_cellsize - p_InputManager.m_MousePosition.m_x;
				double t_dy = i * m_cellsize - p_InputManager.m_MousePosition.m_y;
				double t_dist = sqrt(t_dx * t_dx + t_dy * t_dy);
				if (t_dist > 20)
				{
					m_cells[j][i].AirPressureForce(deltatime, -50 * (t_dx / (t_dist)), 50 * (t_dy / (t_dist)));
				}
			}
			else if(p_InputManager.m_RightMouseDown)
			{
				double t_dx = j * m_cellsize - p_InputManager.m_MousePosition.m_x;
				double t_dy = i * m_cellsize - p_InputManager.m_MousePosition.m_y;
				double t_dist = sqrt(t_dx * t_dx + t_dy * t_dy);
				if (t_dist > 20)
				{
					m_cells[j][i].AirPressureForce(deltatime, 50 * (t_dx / (t_dist)), -50 * (t_dy / (t_dist)));
				}
			}
			else
			{
				m_cells[j][i].AirPressureForce(deltatime, m_xacc, m_yacc);
			}


		}
	}
	//system("CLS");
	//printf("%f", deltatime);
	float hey = 0;
	//system("CLS");
	//for (int i = 0; i < m_numberofcells[1]; i++)
	//{
	//	for (int j = 0; j < m_numberofcells[0]; j++)
	//	{


	//		
	//		totalvolume += m_cells[j][i].m_gas;
	//		/*printf("%f", m_cells[j][i].m_gQ_left);
	//		printf(" CELL ");
	//		printf("%f", m_cells[j][i].m_gQ_right);
	//		printf("  ");
	//		*/
	//	}
	//	printf("\n");
	//}
	//std::cout << std::fixed << std::setprecision(5) << totalvolume << std::endl;
	
	//LateUpdate();
	
	for (int i = 0; i < m_numberofcells[0]; i++)
	{
		for (int j = 0; j < m_numberofcells[1]; j++)
		{

			m_cells[i][j].VelocityUpdate(deltatime);
			//std::cout << std::fixed << std::setprecision(10) << m_cells[i][j].m_pressure << std::endl;
		}
	}
	
	for (int i = 0; i < m_numberofcells[0]; i++)
	{
		for (int j = 0; j < m_numberofcells[1]; j++)
		{
			

			m_cells[i][j].LateUpdate2(deltatime);
			
			
		}
	}
	
	for (int i = 0; i < m_numberofcells[0]; i++)
	{
		for (int j = 0; j < m_numberofcells[1]; j++)
		{
			

			//m_cells[i][j].LateUpdate3(deltatime);


		}
	}
}

void GameState::LateUpdate()
{
	
	
	

}

void GameState::Draw(DrawManager& p_DrawManager) 
{
	for (int i = 0; i < m_numberofcells[0]; i++)
	{
		for (int j = 0; j < m_numberofcells[1]; j++)
		{
			p_DrawManager.Draw(m_cells[i][j]);
		}
	}
}

void GameState::Exit() 
{
	for (int i = 0; i < m_numberofcells[0]; i++)
	{
		delete[] m_cells[i];
	}
	delete[] m_cells;
}
