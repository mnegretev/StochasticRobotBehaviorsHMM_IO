
%get_speed_position("../data/","sim_accelerator.txt")
function get_speed_position(path,name)

%path= "../data/PruebasImu/"
%path= "../data/";
%name = "prueba2_90_derecha.txt"
%name = "prueba2_1m_adelante.txt"
%name = "prueba2_1m_atras.txt"
%name = "sim_accelerator.txt"
file_name=strcat(path,name)



slct=2
string=strcat(name,'  X');
calculate_speed_position(file_name,slct,string)

slct=3
string=strcat(name,'  Y');
calculate_speed_position(file_name,slct,string)

slct=4
string=strcat(name,'  Z');
calculate_speed_position(file_name,slct,string)

slct=5
string=strcat(name,'  GX');
calculate_speed_position(file_name,slct,string)

slct=6
string=strcat(name,'  GY');
calculate_speed_position(file_name,slct,string)

slct=7
string=strcat(name,'  GZ');
calculate_speed_position(file_name,slct,string)

