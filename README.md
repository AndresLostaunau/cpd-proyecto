# cpd-proyecto (RngStreams: generador random)
Uno de los principales objetivos de la generación de números random en paralelo, es lograr la independencia de procesos al generar éstos. Esto colinda con el paralelismo ideal, pero es uno de los fundamentos principales de modelos estocásticos.
Los distintos métodos incluyen:
a) Random spacing: donde los procesos se inicializan en forma random a través de distintos seeds (E.g. Mersenne Twister (MT) generator)
b) Sequence splitting: dividiendo una secuencia en bloques que no se superponen
c) Cycle division: donde el período de un generador se divide en segmentos en forma determinística (Combined Multiple recursive generator (CMRG) with cycle division: RngStreams package)
d) Parametrización: los parámetetros de un generador se modifican para producir distintos streams (Multiplicative lagged Fibonacci generator with parametrization: SPRNG package) 
El método MRG garantiza que los streams no coincidan. Este puede us-arse en forma combinada (CMRG), con mayores ventajas en la generación de random. Son muy estables y estadísticamente seguros. El paquete RngStreams puede ser encontrado aquí. [1]
El desarrollo de la solución del problema debe contener lo siguiente:
a) Elegir un caso de aplicación de las presentadas en el paper adjunto y elaborar un PRAM del mismo.
b) Determinar la complejidad teórica del código y compararla con mediciones de tiempo, para distinto número de procesos y tamaño del problema.
c) Medir la velocidad del algoritmo, y representarla en gráficas. Analizar la escalabilidad del software.
d) Optimizacíon: Desarrollar un software de análisis de performance que se adapte al código utilizado y permita obtener métricas que faciliten el análisis de escalabilidad.
Bibliografía
[1] http://www.iro.umontreal.ca/ lecuyer/myftp/streams00/
[2] https://arxiv.org/pdf/1403.7645.pdf
