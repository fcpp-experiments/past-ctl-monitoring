/*
##########################################################
# FCPP data export started at:  Sat Dec 19 19:31:16 2020 #
##########################################################
# 
#
# The columns have the following meaning:
# time mean(fail<local_safety_monitor>) mean(fail<global_safety_monitor>) 
0 0 0 
1 0 0 
2 0 0 
3 0 0 
4 0 0 
5 0 0 
6 0 0 
7 0 0 
8 0 0 
9 0 0 
10 0 0 
11 0 0 
12 0 0 
13 0 0 
14 0 0 
15 0 0 
16 0 0 
17 0 0 
18 0 0 
19 0 0 
20 0 0 
21 0 0 
22 0 0 
23 0 0 
24 0 0 
25 0 0 
26 0 0 
27 0 0 
28 0 0 
29 0 0 
30 0 0 
31 0 0 
32 0 0 
33 0 0 
34 0 0 
35 0 0 
36 0 0 
37 0 0 
38 0 0 
39 0 0 
40 0 0 
41 0 0 
42 0 0 
43 0 0 
44 0 0 
45 0 0 
46 0 0 
47 0 0 
48 0 0 
49 0 0 
50 0 0 
51 0 0 
52 0 0 
53 0 0 
54 0 0 
55 0 0 
56 0 0 
57 0 0 
58 0 0 
59 0 0 
60 0.06 0.3 
61 0.06 0.6 
62 0.06 0.74 
63 0.06 0.82 
64 0.06 0.87 
65 0.06 0.94 
66 0.06 0.99 
67 0.06 0.99 
68 0.07 0.99 
69 0.07 0.99 
70 0.07 0.99 
71 0.07 0.99 
72 0.07 0.99 
73 0.07 0.99 
74 0.07 0.99 
75 0.07 0.99 
76 0.07 0.99 
77 0.07 0.99 
78 0.07 0.99 
79 0.07 0.99 
80 0.07 0.99 
81 0.07 0.99 
82 0.07 0.99 
83 0.07 0.99 
84 0.07 1 
85 0.07 1 
86 0.07 1 
87 0.07 1 
88 0.07 1 
89 0.07 1 
90 0.07 1 
91 0.07 1 
92 0.07 1 
93 0.07 1 
94 0.07 1 
95 0.07 1 
96 0.07 1 
97 0.08 1 
98 0.08 1 
99 0.08 1 
100 0.08 1 
101 0.08 1 
102 0.08 1 
103 0.08 1 
104 0.08 1 
105 0.08 1 
106 0.08 1 
107 0.08 1 
108 0.08 1 
109 0.08 1 
110 0.08 1 
111 0.08 1 
112 0.08 1 
113 0.08 1 
114 0.08 1 
115 0.08 1 
116 0.08 1 
117 0.09 1 
118 0.09 1 
119 0.09 1 
120 0.09 1 
121 0.09 1 
122 0.09 1 
123 0.09 1 
124 0.09 1 
125 0.09 1 
126 0.09 1 
127 0.09 1 
128 0.09 1 
129 0.09 1 
130 0.09 1 
131 0.09 1 
132 0.09 1 
133 0.09 1 
134 0.09 1 
135 0.09 1 
136 0.09 1 
137 0.09 1 
138 0.09 1 
139 0.09 1 
140 0.09 1 
141 0.09 1 
142 0.09 1 
143 0.09 1 
144 0.09 1 
145 0.09 1 
146 0.09 1 
147 0.09 1 
148 0.09 1 
149 0.09 1 
150 0.09 1 
151 0.09 1 
152 0.09 1 
153 0.09 1 
154 0.09 1 
155 0.09 1 
156 0.09 1 
157 0.09 1 
158 0.09 1 
159 0.09 1 
160 0.09 1 
161 0.09 1 
162 0.09 1 
163 0.09 1 
164 0.09 1 
165 0.09 1 
166 0.09 1 
167 0.09 1 
168 0.09 1 
169 0.09 1 
170 0.09 1 
171 0.09 1 
172 0.09 1 
173 0.09 1 
174 0.09 1 
175 0.09 1 
176 0.09 1 
177 0.09 1 
178 0.09 1 
179 0.09 1 
180 0.09 1 
181 0.09 1 
182 0.09 1 
183 0.09 1 
184 0.09 1 
185 0.09 1 
186 0.09 1 
187 0.09 1 
188 0.09 1 
189 0.09 1 
190 0.09 1 
191 0.09 1 
192 0.09 1 
193 0.09 1 
194 0.09 1 
195 0.09 1 
196 0.09 1 
197 0.09 1 
198 0.09 1 
199 0.09 1 
200 0.09 1 
##########################################################
# FCPP data export finished at: Sat Dec 19 19:32:45 2020 #
##########################################################
*/
// crowd_safety
string name = "crowd_safety";

import "plot.asy" as plot;
unitsize(1cm);

plot.ROWS = 1;
plot.COLS = 1;

plot.put(plot.plot(name+"-timfail", "", "time", "fail", new string[] {"local safety monitor", "global safety monitor"}, new pair[][] {{(0, 0), (1, 0), (2, 0), (3, 0), (4, 0), (5, 0), (6, 0), (7, 0), (8, 0), (9, 0), (10, 0), (11, 0), (12, 0), (13, 0), (14, 0), (15, 0), (16, 0), (17, 0), (18, 0), (19, 0), (20, 0), (21, 0), (22, 0), (23, 0), (24, 0), (25, 0), (26, 0), (27, 0), (28, 0), (29, 0), (30, 0), (31, 0), (32, 0), (33, 0), (34, 0), (35, 0), (36, 0), (37, 0), (38, 0), (39, 0), (40, 0), (41, 0), (42, 0), (43, 0), (44, 0), (45, 0), (46, 0), (47, 0), (48, 0), (49, 0), (50, 0), (51, 0), (52, 0), (53, 0), (54, 0), (55, 0), (56, 0), (57, 0), (58, 0), (59, 0), (60, 0.06), (61, 0.06), (62, 0.06), (63, 0.06), (64, 0.06), (65, 0.06), (66, 0.06), (67, 0.06), (68, 0.07), (69, 0.07), (70, 0.07), (71, 0.07), (72, 0.07), (73, 0.07), (74, 0.07), (75, 0.07), (76, 0.07), (77, 0.07), (78, 0.07), (79, 0.07), (80, 0.07), (81, 0.07), (82, 0.07), (83, 0.07), (84, 0.07), (85, 0.07), (86, 0.07), (87, 0.07), (88, 0.07), (89, 0.07), (90, 0.07), (91, 0.07), (92, 0.07), (93, 0.07), (94, 0.07), (95, 0.07), (96, 0.07), (97, 0.08), (98, 0.08), (99, 0.08), (100, 0.08), (101, 0.08), (102, 0.08), (103, 0.08), (104, 0.08), (105, 0.08), (106, 0.08), (107, 0.08), (108, 0.08), (109, 0.08), (110, 0.08), (111, 0.08), (112, 0.08), (113, 0.08), (114, 0.08), (115, 0.08), (116, 0.08), (117, 0.09), (118, 0.09), (119, 0.09), (120, 0.09), (121, 0.09), (122, 0.09), (123, 0.09), (124, 0.09), (125, 0.09), (126, 0.09), (127, 0.09), (128, 0.09), (129, 0.09), (130, 0.09), (131, 0.09), (132, 0.09), (133, 0.09), (134, 0.09), (135, 0.09), (136, 0.09), (137, 0.09), (138, 0.09), (139, 0.09), (140, 0.09), (141, 0.09), (142, 0.09), (143, 0.09), (144, 0.09), (145, 0.09), (146, 0.09), (147, 0.09), (148, 0.09), (149, 0.09), (150, 0.09), (151, 0.09), (152, 0.09), (153, 0.09), (154, 0.09), (155, 0.09), (156, 0.09), (157, 0.09), (158, 0.09), (159, 0.09), (160, 0.09), (161, 0.09), (162, 0.09), (163, 0.09), (164, 0.09), (165, 0.09), (166, 0.09), (167, 0.09), (168, 0.09), (169, 0.09), (170, 0.09), (171, 0.09), (172, 0.09), (173, 0.09), (174, 0.09), (175, 0.09), (176, 0.09), (177, 0.09), (178, 0.09), (179, 0.09), (180, 0.09), (181, 0.09), (182, 0.09), (183, 0.09), (184, 0.09), (185, 0.09), (186, 0.09), (187, 0.09), (188, 0.09), (189, 0.09), (190, 0.09), (191, 0.09), (192, 0.09), (193, 0.09), (194, 0.09), (195, 0.09), (196, 0.09), (197, 0.09), (198, 0.09), (199, 0.09), (200, 0.09)}, {(0, 0), (1, 0), (2, 0), (3, 0), (4, 0), (5, 0), (6, 0), (7, 0), (8, 0), (9, 0), (10, 0), (11, 0), (12, 0), (13, 0), (14, 0), (15, 0), (16, 0), (17, 0), (18, 0), (19, 0), (20, 0), (21, 0), (22, 0), (23, 0), (24, 0), (25, 0), (26, 0), (27, 0), (28, 0), (29, 0), (30, 0), (31, 0), (32, 0), (33, 0), (34, 0), (35, 0), (36, 0), (37, 0), (38, 0), (39, 0), (40, 0), (41, 0), (42, 0), (43, 0), (44, 0), (45, 0), (46, 0), (47, 0), (48, 0), (49, 0), (50, 0), (51, 0), (52, 0), (53, 0), (54, 0), (55, 0), (56, 0), (57, 0), (58, 0), (59, 0), (60, 0.3), (61, 0.6), (62, 0.74), (63, 0.82), (64, 0.87), (65, 0.94), (66, 0.99), (67, 0.99), (68, 0.99), (69, 0.99), (70, 0.99), (71, 0.99), (72, 0.99), (73, 0.99), (74, 0.99), (75, 0.99), (76, 0.99), (77, 0.99), (78, 0.99), (79, 0.99), (80, 0.99), (81, 0.99), (82, 0.99), (83, 0.99), (84, 1), (85, 1), (86, 1), (87, 1), (88, 1), (89, 1), (90, 1), (91, 1), (92, 1), (93, 1), (94, 1), (95, 1), (96, 1), (97, 1), (98, 1), (99, 1), (100, 1), (101, 1), (102, 1), (103, 1), (104, 1), (105, 1), (106, 1), (107, 1), (108, 1), (109, 1), (110, 1), (111, 1), (112, 1), (113, 1), (114, 1), (115, 1), (116, 1), (117, 1), (118, 1), (119, 1), (120, 1), (121, 1), (122, 1), (123, 1), (124, 1), (125, 1), (126, 1), (127, 1), (128, 1), (129, 1), (130, 1), (131, 1), (132, 1), (133, 1), (134, 1), (135, 1), (136, 1), (137, 1), (138, 1), (139, 1), (140, 1), (141, 1), (142, 1), (143, 1), (144, 1), (145, 1), (146, 1), (147, 1), (148, 1), (149, 1), (150, 1), (151, 1), (152, 1), (153, 1), (154, 1), (155, 1), (156, 1), (157, 1), (158, 1), (159, 1), (160, 1), (161, 1), (162, 1), (163, 1), (164, 1), (165, 1), (166, 1), (167, 1), (168, 1), (169, 1), (170, 1), (171, 1), (172, 1), (173, 1), (174, 1), (175, 1), (176, 1), (177, 1), (178, 1), (179, 1), (180, 1), (181, 1), (182, 1), (183, 1), (184, 1), (185, 1), (186, 1), (187, 1), (188, 1), (189, 1), (190, 1), (191, 1), (192, 1), (193, 1), (194, 1), (195, 1), (196, 1), (197, 1), (198, 1), (199, 1), (200, 1)}}));


shipout("crowd_safety");