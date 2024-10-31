```c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <string.h>

#define MAX_LOCATIONS 100
#define EARTH_RADIUS_KM 6371.0
#define FILENAME "database.txt"

double haversine(double lat1, double lon1, double lat2, double lon2) {
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;
    lat1 = lat1 * M_PI / 180.0;
    lat2 = lat2 * M_PI / 180.0;

    double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return EARTH_RADIUS_KM * c;
}

int loadLocationsFromFile(char places[MAX_LOCATIONS][50], double latitudes[MAX_LOCATIONS], double longitudes[MAX_LOCATIONS]) {
    FILE* file = fopen(FILENAME, "r");
    if (!file) {
        printf("Error: Could not open file %s\n", FILENAME);
        return -1;
    }

    char line[100];
    int index = 0;

    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file) && index < MAX_LOCATIONS) {
        sscanf(line, "Place %*d,%lf,%lf", &latitudes[index], &longitudes[index]);
        sprintf(places[index], "Place %d", index + 1);
        index++;
    }

    fclose(file);
    return index;
}

void calculateDistance(char places[MAX_LOCATIONS][50], double latitudes[MAX_LOCATIONS], double longitudes[MAX_LOCATIONS], int numLocations) {
    int start, end;

    printf("Enter the starting location (1 to %d): ", numLocations);
    scanf("%d", &start);
    printf("Enter the destination location (1 to %d): ", numLocations);
    scanf("%d", &end);

    start--;
    end--;

    if (start < 0 || start >= numLocations || end < 0 || end >= numLocations) {
        printf("Invalid location numbers. Please try again.\n");
        return;
    }

    double distance = haversine(latitudes[start], longitudes[start], latitudes[end], longitudes[end]);
    printf("Distance from %s to %s is: %.2f km\n", places[start], places[end], distance);
}

int main() {
    char places[MAX_LOCATIONS][50];
    double latitudes[MAX_LOCATIONS];
    double longitudes[MAX_LOCATIONS];

    int numLocations = loadLocationsFromFile(places, latitudes, longitudes);
    if (numLocations == -1) {
        return 1;
    }

    calculateDistance(places, latitudes, longitudes, numLocations);

    return 0;
}
```