# FT077A_processamentoAltoDesempenho

Arquivos executados no cluster IBM

$ gcc <arquivo.c> -lpthread (Pthreads)


$ xlc -qsmp -qthreaded -q64 arquivo.c (OpenMP)


$ mpcc –q64 –qarch=pwr7 –qtune=pwr7 arquivo.c –o arquivo (MPI)
