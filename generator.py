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


f = open("dates.txt", "w")
f.seek(0)

for i in range(50):
    if i % 3 == 0:
        argz = {
            "Year": random.choice(year_range),
            "Month": random.choice(month_range),
            "Day": random.choice(day_range),
            "Hour": random.choice(hour_range),
            "Minute": random.choice(min_range),
            "Second": random.choice(second_range),
            "Hour_Offset": random.choice(hour_range),
            "Min_Offset": random.choice(min_range),
        }
        date = pos_iso_format.format(**argz)
    elif i % 3 == 1:
        argz = {
            "Year": random.choice(year_range),
            "Month": random.choice(month_range),
            "Day": random.choice(day_range),
            "Hour": random.choice(hour_range),
            "Minute": random.choice(min_range),
            "Second": random.choice(second_range),
            "Hour_Offset": random.choice(hour_range),
            "Min_Offset": random.choice(min_range),
        }
        date = neg_iso_format.format(**argz)
    else:
        argz = {
            "Year": random.choice(year_range),
            "Month": random.choice(month_range),
            "Day": random.choice(day_range),
            "Hour": random.choice(hour_range),
            "Minute": random.choice(min_range),
            "Second": random.choice(second_range),
        }
        date = gmt_iso_format.format(**argz)

    f.write(date)
f.truncate()
f.close()
