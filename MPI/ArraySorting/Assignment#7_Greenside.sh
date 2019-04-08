#!/bin/bash
#PBS -l nodes=4:ppn=4:physical
#PBS -l walltime=00:10:00
#PBS -o /home/Students/tgreenside/Assignment#7_Greenside/job_out
#PBS -j oe
#PBS -N lab4

date
export PROGRAM="/home/Students/tgreenside/Assignment#7_Greenside/asgn7para"
mpirun -machinefile $PBS_NODEFILE $PROGRAM 40000
mpirun -machinefile $PBS_NODEFILE $PROGRAM 400000
date
exit 0
