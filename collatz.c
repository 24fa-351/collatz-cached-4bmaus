#include "collatz.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
  if (argc != 6) {
    printf("Invalid Inputs\n");
    return 1;
  }

  int user_iteration = atoi(argv[1]);
  int Min = atoi(argv[2]);
  int Max = atoi(argv[3]);
  char *cache_policy = argv[4];
  int cache_size = atoi(argv[5]);

  CachePolicy policy = get_policy(cache_policy);
  Cache *cache = initialize(cache_size);
  if (!cache) {
    return 1;
  }

  srand(time(NULL));
  int hit_count = 0;
  int total_requests = 0;

  FILE *output_file = fopen("output.csv", "w");
  if (output_file == NULL) {
    printf("Error opening output file.\n");
    return 1;
  }

  fprintf(output_file, "Random Number,Steps,Cache Hit Percentage\n");

  for (int ix = 0; ix < user_iteration; ix++) {
    int rand_num = rand() % (Max - Min + 1) + Min;
    unsigned long long int steps = collatz_cached(cache, rand_num, policy, &hit_count, &total_requests);
    
    double hit_percentage = (total_requests == 0) ? 0.0 : (hit_count * 100.0 / total_requests);
    
    fprintf(output_file, "%d,%llu,%.2f%%\n", rand_num, steps, hit_percentage);
  }

  fclose(output_file);

  int hit_misses = total_requests - hit_count;
  printf("Hit Count: %d, Hit Misses: %d, Total Requests: %d\n", hit_count, hit_misses, total_requests);
  
  double final_hit_percentage = (total_requests == 0) ? 0.0 : (hit_count * 100.0 / total_requests);
  printf("Final Cache Hit Percentage: %.2f%%\n", final_hit_percentage);

  free(cache->entries);
  free(cache);
  return 0;
}