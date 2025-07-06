#include <stdio.h>
#include <math.h>

int main(void) {
    double lat1, lon1, lat2, lon2;
    printf("Enter latitude and longitude of point 1 (deg): ");
    if (scanf("%lf %lf", &lat1, &lon1) != 2) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    printf("Enter latitude and longitude of point 2 (deg): ");
    if (scanf("%lf %lf", &lat2, &lon2) != 2) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    const double R = 6371.0; // Earth radius in kilometers
    double rad = M_PI / 180.0;
    lat1 *= rad;
    lon1 *= rad;
    lat2 *= rad;
    lon2 *= rad;

    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;

    double a = sin(dlat / 2) * sin(dlat / 2) +
               cos(lat1) * cos(lat2) * sin(dlon / 2) * sin(dlon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double distance = R * c;

    printf("Great-circle distance: %.3f km\n", distance);
    return 0;
}
