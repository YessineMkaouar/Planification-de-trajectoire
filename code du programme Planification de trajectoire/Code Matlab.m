%la matrice des cout initiale
M = [0 9999 1.41421 2.23607 9999 2.23607 ;
9999 0 9999 3.60555 2.82843 3.60555 ;
1.41421 9999 0 1 9999 1 ;
2.23607 3.60555 1 0 1 9999 ;
9999 2.82843 9999 1 0 1 ;
2.23607 3.60555 1 9999 1 0 ];

%Les Points du graphe

x = [0 4 1 2 2 1];
y = [0 4 1 1 2 2];
plot(x,y,'.k','MarkerSize', 30)
n=length(x);
A=ones(n,n);
for ligne = 1:n
	for colonne = 1:n
		if ((M(ligne,colonne)==0) | (M(ligne,colonne) > 9000))
			A(ligne,colonne)=0;
		end
	end
end

hold on;
for i = 1:n
	for j = 1:n
		x1=[0 0];
		y1=[0 0];
		if (A(i,j)==1)
			x1(1)=x(i);
			y1(1)=y(i);
			x1(2)=x(j);
			y1(2)=y(j);
			plot(x1,y1,'k-','linewidth',1);
		end
	end
end

%Les Points des obstacles

x_obs0=[1 2 2 1];
y_obs0=[1 1 2 2];
h0=fill(x_obs0,y_obs0,'y-');
h0FaceColor = [0 0.25 0.25];

%Le plus court Chemin
PCC_x = [0 1 1 4 4];
PCC_y = [0 2 2 4 4];
plot(PCC_x,PCC_y,'r-','linewidth',2);
plot(PCC_x(1),PCC_y(1),'.r','MarkerSize', 40)
plot(PCC_x(length(PCC_x)),PCC_y(length(PCC_y)),'.r','MarkerSize', 40)
