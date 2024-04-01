# SP_DSA-proj

This program aims to automate the allocation of sports to students into 6 different sports for the program: Chess, Dancing,
Gaming, Running, Swimming and Tennis. One of these 6 sports is a special sport that must have at least 3 students who are 
competition winners of the particular sport. To facilitate the allocation process, students have submitted their top 3 ranking 
of all sports with their name,GPA, and whether they have won any competition in the respective sport before.

There are 4 rounds to allocate students to different programs.

In round 1, the students will be posted to their first choice whenever possible, until the vacancy of the sport is filled up. 
Next is to remove students from those sports that exceed their vacancies. So we sort students inside eachsport with their GPA 
in ascending order. 

After allocating most of the students to their first choice, ‘stealing’ will happen in round 2. As mentioned, there is a special 
sport that must have at least 3 students who have won competition before. To do so, the special sport has been given the permission 
to ‘steal’ students from other sports, meaning students who are already allocated to their first choicemight be removed and moved 
to the special sport. While students who filled up the special sport will be removed and move on to round 3 with unallocated students.

In round 3, students who are not allocated to their first choice or removed from the special sport in round 1 and 2 respectively will 
be posted to their second choice whenever possible.

Similar to round 3, round 4 will be the same except students will be allocated to their third choice. The remaining students who are not 
allocated to any sport will be randomly posted to sports with vacancies.
