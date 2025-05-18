#include <iostream>
#include <locale.h>
#include <vector>

#include <string>
#include <math.h>

using namespace std;

struct UAV_position_regular_system
{
	struct Current_coord
	{
		double x,y,z;
	};
	
	struct Goal_coord
	{
		double x,y,z;
	};
	
	struct Start_coord
	{
		double x = 0.0, y = 0.0, z = 0.0; 
	};
	
	public:
		void set_start_position(double Sx, double Sy, double Sz)
		{
			start_position.x = Sx;
			start_position.y = Sy;
			start_position.z = Sz;
		}
		
		Start_coord get_start_position()
		{
			return start_position;		
		}
		
		void set_uav_position(double Dx, double Dy, double Dz)
		{
			uav_coord.x = Dx - start_position.x;
			uav_coord.y = Dy - start_position.y;
			uav_coord.z = Dz - start_position.z;
		}
		
		Current_coord get_uav_position()
		{
			return uav_coord;		
		}
		
		void set_goal_position(double Gx, double Gy, double Gz)
		{
			goal_coord.x = Gx;
			goal_coord.y = Gy;
			goal_coord.z = Gz;
		}
		
		Goal_coord get_goal_position()
		{
			return goal_coord;		
		}
		
		void culculate_distance_to_goal()
		{
			distance_to_goal = sqrt(pow(goal_coord.x - uav_coord.x,2)+pow(goal_coord.y - uav_coord.y,2)+pow(goal_coord.z - uav_coord.z,2));
		}
		
		double get_distance_to_goal()
		{
			return distance_to_goal;
		}
		
		void culculate_direction_cos()
		{
			dir_cos.resize(4);
			
			dir_cos.at(0) = (goal_coord.x-uav_coord.x)/distance_to_goal;
			dir_cos.at(1) = (goal_coord.y-uav_coord.y)/distance_to_goal;
			dir_cos.at(2) = (goal_coord.z-uav_coord.z)/distance_to_goal;
		}
		
		vector<double> get_direction_cos()
		{
			return dir_cos;
		}
		
		void set_speed_limit(double limit)
		{
			speed_limit = limit;
		}
		
		double get_speed_limit()
		{
			return speed_limit;
		}
		
		vector<double> get_speeds()
		{
			speeds.resize(3);			
			if(distance_to_goal < speed_limit)
			{				
				speeds.at(0) = distance_to_goal*dir_cos.at(0);
				speeds.at(1) = distance_to_goal*dir_cos.at(1);
				speeds.at(2) = distance_to_goal*dir_cos.at(2);
			}
			else
			{
				speeds.at(0) = speed_limit*dir_cos.at(0);
				speeds.at(1) = speed_limit*dir_cos.at(1);
				speeds.at(2) = speed_limit*dir_cos.at(2);
			}
			
			return speeds;
		}	
	private:
		Current_coord uav_coord;
		Goal_coord goal_coord;
		Start_coord start_position;
		
		double speed;
		vector<double> dir_cos;
		vector<double> speeds;
		double distance_to_goal = 0;
		double speed_limit;
};
int main()
{
	setlocale(LC_ALL,"russian");
	
    UAV_position_regular_system UAV_PRS;
    UAV_position_regular_system::Start_coord start_position;
    UAV_position_regular_system::Current_coord uav_position;
    UAV_position_regular_system::Goal_coord goal_position;
    
    vector<double> sp;
    vector<double> up;
    vector<double> gp;
    vector<double> dir_cos;
    vector<double>speeds;
    
    double dtg;
    double sl;
    
    sp.resize(3);
    up.resize(3);
    gp.resize(3);
	dir_cos.resize(4);
	speeds.resize(3);
	
	cout << "===============Система позиционного регулирования БЛА===============" << endl;
	cout << "Введите координаты стартовой позиции:" << endl;
	cin >> sp.at(0);
	cin >> sp.at(1);
	cin >> sp.at(2);
	cout << "Введите координаты текущей позиции аппарата:" << endl;
	cin >> up.at(0);
	cin >> up.at(1);
	cin >> up.at(2);
	cout << "Введите координаты целевой позиции аппарата:" << endl;
	cin >> gp.at(0);
	cin >> gp.at(1);
	cin >> gp.at(2);
	
	cout << "Введите максимальное значение скорости:" << endl;
	cin >> sl;
	
    UAV_PRS.set_start_position(sp.at(0),sp.at(1),sp.at(2));
    UAV_PRS.set_uav_position(up.at(0),up.at(1),up.at(2));
    UAV_PRS.set_goal_position(gp.at(0),gp.at(1),gp.at(2));
    
    UAV_PRS.set_speed_limit(sl);
	UAV_PRS.culculate_distance_to_goal();
	UAV_PRS.culculate_direction_cos();
	
	dir_cos = UAV_PRS.get_direction_cos();
	speeds = UAV_PRS.get_speeds();
	
	start_position = UAV_PRS.get_start_position();
	uav_position = UAV_PRS.get_uav_position();
	goal_position = UAV_PRS.get_goal_position();
	
	cout << "\nКоординаты начальной позиции аппарата: [" << start_position.x <<", " << start_position.y << ", " << start_position.z << "]" << endl;
	cout << "Координаты текущей позиции аппарата: [" << uav_position.x <<", " << uav_position.y << ", " << uav_position.z << "]" << endl;
	cout << "Координаты целевой позиции аппарата: [" << goal_position.x <<", " << goal_position.y << ", " << goal_position.z << "]" << endl;
	cout << "Максимальное значение скорости аппарата: " << sl << endl;
	cout << "Расстояние до точки: " << UAV_PRS.get_distance_to_goal() << endl;
	cout << "Направляющие косинусы: [" << dir_cos.at(0) << ", " << dir_cos.at(1) << ", " << dir_cos.at(2) << "]" << endl;
	cout << "Итоговые значения скоростей: [" << speeds.at(0) << ", " << speeds.at(1) << ", " << speeds.at(2) << "]" << endl;
}
