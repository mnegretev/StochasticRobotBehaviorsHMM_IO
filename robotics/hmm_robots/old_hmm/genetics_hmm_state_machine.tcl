
toplevel .input

# Global variables
global check_population

# Genetics Panel
# Labels
label .input.label_num_points -text "Number of individuals"
label .input.label_num_regions -text "Number of generations"
label .input.label_epsilon -text "Mutation rate"
label .input.label_crossing -text "Crossing rate"
label .input.label_name -text "Population's name"
label .input.label_num_best -text "% of best individuals"

# Entries
entry .input.num_points -width 5 -textvariable num_points -foreground green -background blue
.input.num_points insert 0 "100"
entry .input.num_regions -width 5 -textvariable num_regions -foreground green -background blue
.input.num_regions insert 0 "100"
entry .input.epsilon -width 5 -textvariable mutation_rate -foreground green -background blue
.input.epsilon insert 0 "0.1"
entry .input.crossing -width 5 -textvariable crossing_rate -foreground green -background blue
.input.crossing insert 0 "0.8"
entry .input.name -width 10 -textvariable name -foreground green -background blue
.input.name insert 0 "avoid"
entry .input.num_best -width 5 -textvariable num_best -foreground green -background blue
.input.num_best insert 0 ".10"

set check_population 1
checkbutton .check_population -text "Use new population" -variable check_population
set check_vasconcelos 0
checkbutton .check_vasconcelos -text "Use Vasconcelos" -variable check_vasconcelos
set check_destination 0
checkbutton .check_dest -text "Use straigh destination" -variable check_dest
set random 0
checkbutton .check_random -text "Add noise" -variable random
set prb_out 0
checkbutton .check19 -text "Stochastic Outputs" -variable prb_out
set get_st 1
checkbutton .check20 -text "Get Algorithm FSM" -variable get_st

pack .check_population .check_vasconcelos .check_dest .check_random .check20 .check19



# Execute Button
button .input.b -text START -activebackground red -activeforeground orange -command  { 

# Global variables
global check_population
global check_vasconcelos
global check_dest


 set sum_fits "sum_fits.dat"
 set average_fits "average_fits.dat"
 set worst_fits "worst_fits.dat"
 set fitness_file "fitness.dat"
 set fitness_ "fitness"
 set fitness_population "fitness_population.dat"
 set average_fitness_population "average_fitness_population.dat"
 set worst_fitness_population "worst_fitness_population.dat"
 set observations observations_hmm/
 set path_observations $path$observations
 set file_xytheta "random"
 set state_machine state_machine.txt
 set fsm_memory fsm_memory.prb
 set hmm_fsm hmm_fsm.prb
 set gen_0 gen_0.raw
 set gen_0_ gen_0_

 set program_goto robots/ViRbot/GoTo_sim_MV_SNRS_tcp
 set program $path$program_goto 
 set program_transform robots/genetics/genetics_state_machine/transform_gen
 set transform $path$program_transform
 set command "cp"
 set cat "cat"
 set delete "rm"
 set program_gen robots/genetics/genetics_state_machine/genetics_general 
 set gen $path$program_gen 
 set num_ind $num_points
 set num_gen $num_regions
 set n_best $num_best

 # -x 16 -y 112 -v 271 -z 111
 # -x 5 -y 380 -v 282 -z 380
 # -x 25 -y 379 -v 146 -z 497
 # -x 33 -y 383 -v 250 -z 386
 # -x 43 -y 135 -v 261 -z 138
 #set x 3
 #set y 135
 #set v 279
 #set z 138
 set line "_"
 set line_hmm "hmm_"
 set name_pop $name
 set hmm_name_pop_ $line_hmm$name$line
 set line_prb "_prb"
 set line_gen "_gen_0.raw"
 set line_map "_map_0.raw"
 set line_map_0 "_map_0_"
 set name_pop_ "$name_pop$line"
 set cero "0"
 set name_pop_0 "$hmm_name_pop_$cero.dat"
 #set name_pop_prb "$name_pop$line_prb"
 #set name_pop_prb_ "hmm_$name_pop$line_prb$line"
 #set name_pop_prb_0 "hmm_$name_pop$line_prb$line$cero.dat"
 set laser_file  "laser_$map$line_gen"
 set laser_file_data  "laser_$map$line_map"
 set laser_file_data_0  "laser_$map$line_map_0"
 #set inc_x 1
 #set inc_y 10 
 #set inc_v 1
 #set inc_z 10
 set x [expr $xx - $incxx]
 set y [expr $yy - $incyy]
 set v [expr $vv - $incvv]
 set z [expr $zz - $inczz]

 #set x $xx
 #set y $yy
 #set v $vv
 #set z $zz
 #set final_x [expr $x + 100]
 #set final_y [expr $y + 200]
 #set final_v [expr $v + 100]
 #set final_z [expr $z + 200]
 set initial_x $x
 set initial_y $y
 set initial_v $v
 set initial_z $z
 set initial_angle $angle
 set num_bits_states $num_bits_st
 set num_bits_outputs $num_bits_out
 set num_symbols [expr 2 << ($num_bits_in -1) ]
 #set num_bits_individuals [expr [expr $num_bits_states + $num_bits_outputs] * [expr 2 << [expr $num_bits_states + $num_inputs -1 ]] ]
 set num_states [expr 2 <<  ($num_bits_states - 1) ]
 set num_outputs [expr 2 << ($num_bits_outputs - 1) ]
 set num_symbols [expr 2 << ($num_bits_in - 1) ]

 set num_Pi [expr $num_states]
 set num_A [expr $num_states * $num_states]
 set num_B [expr $num_states * $num_symbols]
 set num_C [expr $num_states * $num_symbols * $num_outputs]
 set num_prb 8
 set num_bits_individuals [expr $num_prb * ( $num_Pi + $num_A + $num_B + $num_C)]
 puts "num_bits_individuals $num_bits_individuals"





 if { $check_vasconcelos == 1 } {
	 set num_individuals [expr $num_ind * 2]
 } else { 
	set num_individuals $num_ind
 }

  #It deletes the fitness file fitness_population.dat      
 puts "$delete $path_observations$fitness_population"
 catch {exec $delete $path_observations$fitness_population} result
 #puts $result

 #It deletes the average fitness file average_fitness_population.dat      
 puts "$delete $path_observations$average_fitness_population"
 catch {exec $delete $path_observations$average_fitness_population} result
 #puts $result

 #It deletes the worst fitness file worst_fitness_population.dat      
 puts "$delete $path_observations$worst_fitness_population"
 catch {exec $delete $path_observations$worst_fitness_population} result
 #puts $result


if { $check_population == 1 } {

        #puts "rm /home/savage/observations/$name_pop*.dat"
        #catch {exec rm /home/savage/observations/$name_pop_*.dat} result
        #puts $result
        if { $check_vasconcelos == 0 } {
                puts "$gen genera standard $path_observations $num_ind $num_bits_individuals $name_pop"
                catch {exec $gen genera standard $path_observations $num_ind $num_bits_individuals $name_pop  > test.dat 2> error.dat} result
        } else {
                puts "$gen genera vasconcelos $path_observations $num_ind $num_bits_individuals $name_pop"
                catch {exec $gen genera vasconcelos $path_observations $num_ind $num_bits_individuals $name_pop  > test.dat 2> error.dat} result
        }
        #puts $result
        set check_population 0
 }



 set file [open $path_observations$file_xytheta.ord r]
 set dummy [gets $file num_pnts]

 puts "num_points $num_pnts"
 for {set j 1} {$j <= $num_pnts} {incr j} {
                        set dummy [gets $file xxx($j)]
                        puts "xxx($j) $xxx($j)"
                        set dummy [gets $file yyy($j)]
                        puts "yyy($j) $yyy($j)"
                        set dummy [gets $file vvv($j)]
                        puts "vvv($j) $vvv($j)"
                        set dummy [gets $file zzz($j)]
                        puts "zzz($j) $zzz($j)"
 }

 close $file

 

 for {set i 0} {$i< $num_gen} {incr i} {
   	puts "i  $i"

	set average_generation 0
	set worst_generation 0
    	set bigger 0
 	set worst 1000000
    	set index 0
	set index_worst 0


   	set x [expr $x + $incxx]
   	set y [expr $y + $incyy]
   	set v [expr $v + $incvv]
   	set z [expr $z + $inczz]
   	set angle [expr $angle + $inctheta]

   	if { $x > $endxx } {
        	set x $initial_x
   	}

   	if { $y > $endyy } {
        	set y $initial_y
   	}

   	if { $v > $endvv } {
        	set v $initial_v
   	}

   	if { $z > $endzz } {
        	set z $initial_z
   	}

   	if { $angle > $endtheta } {
        	set $angle $initial_angle
   	}

	if { $check_dest == 1 } {
         set angle1 [expr $angle * -1]
         set radius [expr $advance * 200]
         set randNum_x [expr { int(20 * rand()) }]
         set randNum_y [expr { int(20 * rand()) }]
         set v [expr { $radius * cos($angle1) + $x + $randNum_x}]
         set z [expr { $radius * sin($angle1) + $y + $randNum_y}]

 	}


 	#It deletes the fitness file fitness.dat      
 	#puts "$delete /home/savage/observations/fitness.dat"
 	#catch {exec $delete /home/savage/observations/fitness.dat} result

	puts "$delete $path_observations$fitness_file"
        catch {exec $delete $path_observations$fitness_file} result
 	puts $result


	# It transform the raw bits to a state machine structure 
    puts "$transform state_machine_hmm $path_observations $num_individuals $num_states $num_outputs $num_bits_in $num_symbols $num_bits_individuals $name_pop $num_prb"
    catch {exec $transform state_machine_hmm $path_observations $num_individuals $num_states $num_outputs $num_bits_in $num_symbols $num_bits_individuals $name_pop $num_prb > test_transform.dat 2> error.dat} result
    puts $result


	#puts "$program -e $map -x $x -y $y -v $v -z $z -r 2001 -a localhost -w 2005 -s laser -i 2002 -j localhost -k 2006 -l 16 -n 32 -t $angle -f 0 -g 0 -q 0 -m 0 -p $advance -o $random -prb_out $prb_out"

 for {set j 0} {$j<$num_individuals} {incr j} {
   	puts "$i  $j"

	set sum 0

	 puts "********************************************"


	# It copies the individual to state_machine_hmm.txt
	puts "$command $path_observations$hmm_name_pop_$j.dat $path_observations$hmm_fsm"
	catch {exec $command $path_observations$hmm_name_pop_$j.dat $path_observations$hmm_fsm} result
	puts $result


	set sum 0

	for {set num_pnt 1} {$num_pnt<=$num_pnts} {incr num_pnt} {

		set x $xxx($num_pnt)
                set y $yyy($num_pnt)
                set v $vvv($num_pnt)
                set z $zzz($num_pnt)

		puts "Generation $i individual $j origen Xo $x Yo $y Angle $angle destination Xd $v Yd $z"

		# It executes GoTo with HMMs
                puts "$program -e $map -x $x -y $y -v $v -z $z -r 2001 -a localhost -w 2005 -s laser -i 2002 -j localhost -k 2006 -l 16 -n 32 -t $angle -f 0 -g 0 -q 4 -m 0 -p $advance -o $random -path $path_observations"

                catch {exec $program -e $map -x $x -y $y -v $v -z $z -r 2001 -a localhost -w 2005 -s laser -i 2002 -j localhost -k 2006 -l 16 -n 32 -t $angle -f 0 -g 0 -q 4 -m 0  -p $advance -o $random -path $path_observations > test.dat 2> error.dat} result
                #puts $result





		# it shows the individual's fitness value
		set file [open $path_observations$laser_file r]
		puts "read fitness result file $path_observations$laser_file"
        	set fitness [read $file]
        	#set num_stuck [read $file]
		#set num_obs [read $file]
		puts "fitness $fitness"
        	close $file

		#puts "$cat $path_observations$laser_file"
		#catch {exec $cat $path_observations$laser_file} result
		#puts "cat $result"

		set sum [expr $sum + $fitness]



		if { $j == 0} {
			set jj [expr $num_pnt + $num_individuals ]
        		puts "it copies the robots' movement of the best individual in $jj"
        		puts "$command $path_observations$laser_file_data $path_observations$laser_file_data_0$jj.raw"
        		catch {exec $command $path_observations$laser_file_data $path_observations$laser_file_data_0$jj.raw } result
        		puts $result
		}


	}

        set sum_div [expr $sum/$num_pnts]
	puts "average fitness individual $sum_div"


        if { $sum_div > $bigger } {
                        set bigger $sum_div
                        set index $j
        }

        if { $sum_div < $worst } {
                        set worst $sum_div
                        set index_worst $j
        }

        set average_generation [expr $average_generation + $sum_div]

  	puts "$command $path_observations$laser_file $path_observations$gen_0"
  	catch {exec $command $path_observations$laser_file $path_observations$gen_0 } result

  	# it adds the individual's fitness value to the population fitness
  	#puts "$cat /home/savage/observations/$laser_file >> /home/savage/observations/fitness.dat"
  	#catch {exec $cat /home/savage/observations/$laser_file >> /home/savage/observations/fitness.dat} result
  	#puts "$cat $path_observations$laser_file >> $path_observations$fitness_file"
  	#catch {exec $cat $path_observations$laser_file >> $path_observations$fitness_file} result

  	puts "echo $sum_div >> $path_observations$fitness_file"
  	catch {exec echo $sum_div >> $path_observations$fitness_file} result


	#It copies the robot's movement, ex: laser_random_map_0_1.raw 
	set jj [expr $j +1]
	puts "it copies the robots' movement of $j in $jj"
  	puts "$command $path_observations$laser_file_data $path_observations$laser_file_data_0$jj.raw"
  	catch {exec $command $path_observations$laser_file_data $path_observations$laser_file_data_0$jj.raw } result
	puts $result
   }       

   
   
  
   #It copies the fitnees of the population to fittnees_*.dat     
   puts "$command $path_observations$fitness_file $path_observations$fitness_$i.dat"
   #catch {exec $command /home/savage/observations/fitness.dat /home/savage/observations/fitness_$i.dat} result
   catch {exec $command $path_observations$fitness_file $path_observations$fitness_$i.dat} result

   #It generates a new population
   if { $get_st == 1} {

   	puts "It generates a new population"
   	if { $check_vasconcelos == 0 } {
   		puts "$gen standard $path_observations $num_ind $num_bits_individuals $name_pop $mutation_rate $crossing_rate $n_best"
   		catch {exec $gen standard $path_observations $num_ind $num_bits_individuals $name_pop $mutation_rate $crossing_rate $n_best} result
   	} else {

   		puts "$gen vasconcelos $path_observations $num_ind $num_bits_individuals $name_pop $mutation_rate $crossing_rate $n_best"
   		catch {exec $gen vasconcelos $path_observations $num_ind $num_bits_individuals $name_pop $mutation_rate $crossing_rate $n_best} result

   	}

     }



    puts "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
    puts "generation $i"

     #it saves the fitness of the best individual 
     set fo [open $path_observations$sum_fits w]
     puts $fo $bigger
     #puts "fitness $bigger"
     close $fo
     catch {exec $cat $path_observations$sum_fits >> $path_observations$fitness_population} result
     puts "Best individual $index fitness $bigger"


     #It saves the average of the population fitness  
     set average_generation [expr $average_generation / $num_individuals]
     set fo [open $path_observations$average_fits w]
     puts $fo $average_generation
     close $fo
     puts "Average generation $average_generation"
     puts "$cat $path_observations$average_fits >> $path_observations$average_fitness_population"
     catch {exec $cat $path_observations$average_fits >> $path_observations$average_fitness_population} result


     #It saves the worst individual fitness  
     set fo [open $path_observations$worst_fits w]
     puts $fo $worst
     close $fo
     puts "Worst individual $index_worst fitness $worst"
     puts "$cat $path_observations$worst_fits >> $path_observations$worst_fitness_population"
     catch {exec $cat $path_observations$worst_fits >> $path_observations$worst_fitness_population} result


 }


  #it calculates the perfomance of the last individual
  # It copies the best individual to state_machine.txt 
  puts "$command $path_observations$name_pop_0 $path_observations$hmm_fsm"
  catch {exec $command $path_observations$name_pop_0 $path_observations$hmm_fsm } result
  puts $result



# It executes GoTo with HMMs
 puts "$program -e $map -x $x -y $y -v $v -z $z -r 2001 -a localhost -w 2005 -s laser -i 2002 -j localhost -k 2006 -l 16 -n 32 -t $angle -f 0 -g 0 -q 4 -m 0 -p $advance -o $random -path $path_observations"

 catch {exec $program -e $map -x $x -y $y -v $v -z $z -r 2001 -a localhost -w 2005 -s laser -i 2002 -j localhost -k 2006 -l 16 -n 32 -t $angle -f 0 -g 0 -q 4 -m 0  -p $advance -o $random -path $path_observations > test.dat 2> error.dat} result
 #puts $result




  #It copies the result to gen_*.raw	
  #puts "$command /home/savage/observations/$laser_file /home/savage/observations/gen_0.raw"
  #catch {exec $command /home/savage/observations/$laser_file /home/savage/observations/gen_0.raw} result
  puts "$command $path_observations$laser_file $path_observations$gen_0"
  catch {exec $command $path_observations$laser_file $path_observations$gen_0 } result
  puts $result

  #set file [open /home/savage/observations/$laser_file r]
  set file [open $path_observations/$laser_file r]
  set fitness [read $file]
  puts "Best individual fitness $fitness"
  close $file

}




# Grid input
grid config .input.label_num_points -column 0 -row 0 -sticky e
grid config .input.num_points -column 1 -row 0 -sticky snew
grid config .input.label_num_regions -column 2 -row 0 -sticky e
grid config .input.num_regions -column 3 -row 0 -sticky snew
grid config .input.label_epsilon -column 0 -row 1 -sticky e
grid config .input.epsilon -column 1 -row 1 -sticky snew
grid config .input.label_name -column 2 -row 1 -sticky e
grid config .input.name -column 3 -row 1 -sticky snew
grid config .input.label_crossing -column 0 -row 3 -sticky e
grid config .input.crossing -column 1 -row 3 -sticky snew
grid config .input.b -column 3 -row 4 -sticky snew
grid config .input.label_num_best -column 2 -row 3 -sticky e
grid config .input.num_best -column 3 -row 3 -sticky snew


# Simulation Panel
# Labels
toplevel .sim
label .sim.label_x -text "X"
label .sim.label_y -text "Y"
label .sim.label_v -text "V"
label .sim.label_z -text "Z"
label .sim.label_angle -text "Theta"
label .sim.label_map -text "Map"
label .sim.label_advance -text "Advance"
label .sim.label_path -text "path"
label .sim.label_incx -text "IncX"
label .sim.label_incy -text "IncY"
label .sim.label_incv -text "IncV"
label .sim.label_incz -text "IncZ"
label .sim.label_inctheta -text "IncTheta"
label .sim.label_endx -text "EndX"
label .sim.label_endy -text "EndY"
label .sim.label_endv -text "EndV"
label .sim.label_endz -text "EndZ"
label .sim.label_endtheta -text "EndTheta"

# Entries
entry .sim.x -width 5 -textvariable xx -foreground green -background blue
#.sim.x insert 0 "130"
.sim.x insert 0 "160"
entry .sim.y -width 5 -textvariable yy -foreground green -background blue
.sim.y insert 0 "190"
#.sim.y insert 0 "150"
entry .sim.v -width 5 -textvariable vv -foreground green -background blue
.sim.v insert 0 "350"
#.sim.v insert 0 "300"
entry .sim.z -width 5 -textvariable zz -foreground green -background blue
.sim.z insert 0 "190"
#.sim.z insert 0 "150"
entry .sim.angle -width 5 -textvariable angle -foreground green -background blue
#.sim.angle insert 0 "4.5"
.sim.angle insert 0 "0.0"
entry .sim.map -width 20 -textvariable map -foreground green -background blue
.sim.map insert 0 "random"
entry .sim.advance -width 5 -textvariable advance -foreground green -background blue
.sim.advance insert 0 "1.5"
entry .sim.path -width 40 -textvariable path -foreground green -background blue
.sim.path insert 0 "/home/savage/"
entry .sim.incx -width 5 -textvariable incxx -foreground green -background blue
.sim.incx insert 0 "0"
entry .sim.incy -width 5 -textvariable incyy -foreground green -background blue
.sim.incy insert 0 "0"
entry .sim.incv -width 5 -textvariable incvv -foreground green -background blue
.sim.incv insert 0 "0"
entry .sim.incz -width 5 -textvariable inczz -foreground green -background blue
.sim.incz insert 0 "0"
entry .sim.inctheta -width 5 -textvariable inctheta -foreground green -background blue
.sim.inctheta insert 0 "0"
entry .sim.endx -width 5 -textvariable endxx -foreground green -background blue
.sim.endx insert 0 "140"
entry .sim.endy -width 5 -textvariable endyy -foreground green -background blue
.sim.endy insert 0 "400"
entry .sim.endv -width 5 -textvariable endvv -foreground green -background blue
.sim.endv insert 0 "440"
entry .sim.endz -width 5 -textvariable endzz -foreground green -background blue
.sim.endz insert 0 "400"
entry .sim.endtheta -width 5 -textvariable endtheta -foreground green -background blue
.sim.endtheta insert 0 "0.7075"




# Grid sim
grid config .sim.label_x -column 0 -row 0 -sticky e
grid config .sim.x -column 1 -row 0 -sticky snew
grid config .sim.label_y -column 2 -row 0 -sticky e
grid config .sim.y -column 3 -row 0 -sticky snew
grid config .sim.label_v -column 0 -row 1 -sticky e
grid config .sim.v -column 1 -row 1 -sticky snew
grid config .sim.label_z -column 2 -row 1 -sticky e
grid config .sim.z -column 3 -row 1 -sticky snew
grid config .sim.label_angle -column 0 -row 2 -sticky e
grid config .sim.angle -column 1 -row 2 -sticky snew
grid config .sim.label_map -column 2 -row 2 -sticky snew
grid config .sim.map -column 3 -row 2 -sticky snew
grid config .sim.label_advance -column 0 -row 3 -sticky e
grid config .sim.advance -column 1 -row 3 -sticky snew
grid config .sim.label_path -column 2 -row 3 -sticky e
grid config .sim.path -column 3 -row 3 -sticky snew
grid config .sim.label_endx -column 4 -row 2 -sticky e
grid config .sim.endx -column 5 -row 2 -sticky snew
grid config .sim.label_endy -column 6 -row 2 -sticky e
grid config .sim.endy -column 7 -row 2 -sticky snew
grid config .sim.label_endv -column 4 -row 3 -sticky e
grid config .sim.endv -column 5 -row 3 -sticky snew
grid config .sim.label_endz -column 6 -row 3 -sticky e
grid config .sim.endz -column 7 -row 3 -sticky snew
grid config .sim.label_incx -column 4 -row 0 -sticky e
grid config .sim.incx -column 5 -row 0 -sticky snew
grid config .sim.label_incy -column 6 -row 0 -sticky e
grid config .sim.incy -column 7 -row 0 -sticky snew
grid config .sim.label_incv -column 4 -row 1 -sticky e
grid config .sim.incv -column 5 -row 1 -sticky snew
grid config .sim.label_incz -column 6 -row 1 -sticky e
grid config .sim.incz -column 7 -row 1 -sticky snew
grid config .sim.label_inctheta -column 4 -row 4 -sticky e
grid config .sim.inctheta -column 5 -row 4 -sticky snew
grid config .sim.label_endtheta -column 6 -row 4 -sticky e
grid config .sim.endtheta -column 7 -row 4 -sticky snew



# State Machine panel
toplevel .st

# Labels state
label .st.label_num_states -text "Number of state bits "
label .st.label_num_outputs -text "Number of output bits"
label .st.label_num_inputs -text "Number of inputs"

# Entries state
entry .st.num_states -width 5 -textvariable num_bits_st -foreground green -background blue
.st.num_states insert 0 "5"
entry .st.num_outputs -width 5 -textvariable num_bits_out -foreground green -background blue
.st.num_outputs insert 0 "3"
entry .st.num_inputs -width 5 -textvariable num_bits_in -foreground green -background blue
.st.num_inputs insert 0 "5"

# Grid state
grid config .st.label_num_states -column 0 -row 0 -sticky e
grid config .st.num_states -column 1 -row 0 -sticky snew
grid config .st.label_num_outputs -column 2 -row 0 -sticky e
grid config .st.num_outputs -column 3 -row 0 -sticky snew
grid config .st.label_num_inputs -column 0 -row 1 -sticky e
grid config .st.num_inputs -column 1 -row 1 -sticky snew



grid config .input.label_name -column 2 -row 1 -sticky e
grid config .input.name -column 3 -row 1 -sticky snew

