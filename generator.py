#!/usr/bin/env python3
import random

pos_iso_format = (
    "{Year}-{Month}-{Day}T{Hour}:{Minute}:{Second}+{Hour_Offset}:{Min_Offset}\n"
)
neg_iso_format = (
    "{Year}-{Month}-{Day}T{Hour}:{Minute}:{Second}-{Hour_Offset}:{Min_Offset}\n"
)
gmt_iso_format = "{Year}-{Month}-{Day}T{Hour}:{Minute}:{Second}Z\n"


year_range = [str(i).zfill(4) for i in range(0, 9999)]
month_range = [str(i).zfill(2) for i in range(1, 12)]
day_range = [str(i).zfill(2) for i in range(1, 31)]
hour_range = [str(i).zfill(2) for i in range(0, 23)]
min_range = [str(i).zfill(2) for i in range(0, 59)]
second_range = min_range


invalid_year_range = [str(i) for i in range(0, 15000)]
invalid_month_range = [str(i) for i in range(1, 50)]
invalid_day_range = [str(i)for i in range(1, 50)]
invalid_hour_range = [str(i) for i in range(0, 50)]
invalid_min_range = [str(i) for i in range(0, 75)]
invalid_second_range = min_range


f = open("./out/dates.txt", "w")
f.seek(0)

for i in range(100):
    if i % 3 == 0:
        argz = {
            "Year": random.choice(invalid_year_range),
            "Month": random.choice(invalid_month_range),
            "Day": random.choice(invalid_day_range),
            "Hour": random.choice(invalid_hour_range),
            "Minute": random.choice(invalid_min_range),
            "Second": random.choice(invalid_second_range),
            "Hour_Offset": random.choice(invalid_hour_range),
            "Min_Offset": random.choice(invalid_min_range),
        }
        date = pos_iso_format.format(**argz)
    elif i % 3 == 1:
        argz = {
            "Year": random.choice(invalid_year_range),
            "Month": random.choice(invalid_month_range),
            "Day": random.choice(invalid_day_range),
            "Hour": random.choice(invalid_hour_range),
            "Minute": random.choice(invalid_min_range),
            "Second": random.choice(invalid_second_range),
            "Hour_Offset": random.choice(invalid_hour_range),
            "Min_Offset": random.choice(invalid_min_range),
        }
        date = neg_iso_format.format(**argz)
    else:
        argz = {
            "Year": random.choice(invalid_year_range),
            "Month": random.choice(invalid_month_range),
            "Day": random.choice(invalid_day_range),
            "Hour": random.choice(invalid_hour_range),
            "Minute": random.choice(invalid_min_range),
            "Second": random.choice(invalid_second_range),
        }
        date = gmt_iso_format.format(**argz)

    f.write(date)
f.truncate()
f.close()
