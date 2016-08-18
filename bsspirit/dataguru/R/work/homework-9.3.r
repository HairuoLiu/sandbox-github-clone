#9.3
x<- c(1.000, 0.846, 0.805, 0.859, 0.473, 0.398, 0.301, 0.382,
      0.846, 1.000, 0.881, 0.826, 0.376, 0.326, 0.277, 0.277, 
      0.805, 0.881, 1.000, 0.801, 0.380, 0.319, 0.237, 0.345, 
      0.859, 0.826, 0.801, 1.000, 0.436, 0.329, 0.327, 0.365, 
      0.473, 0.376, 0.380, 0.436, 1.000, 0.762, 0.730, 0.629, 
      0.398, 0.326, 0.319, 0.329, 0.762, 1.000, 0.583, 0.577, 
      0.301, 0.277, 0.237, 0.327, 0.730, 0.583, 1.000, 0.539, 
      0.382, 0.415, 0.345, 0.365, 0.629, 0.577, 0.539, 1.000)
names<-c("x1", "x2", "x3", "x4", "x5", "x6", "x7", "x8")
# names<=c("身高","手臂长","上肢长","下肢长","体重","颈围","胸围","胸宽")
R<-matrix(x, nrow=8, dimnames=list(names, names))

source("factor.analy.R")
fa<-factor.analy(R,m=2,method="princomp");
fa<-factor.analy(R,m=2,method="likelihood");
# E<-R-fa$loadings %*% t(fa$loadings) - diag(fa$var[,2])
# sum(E^2)

vm1<-varimax(fa$loadings,normalize=FALSE)
fa2<-factanal(factors=2,covmat=R)



library(psych)
# covariances<-ability.cov$cov
# correlations<-cov2cor(covariances)
# fa.parallel(R,n.obs=112,fa="fa",n.iter=100,show.legend=FALSE)
fa<-fa(R,nfactors=2,rotate="varimax",fm="pa" )

factor.plot(fa,labels=rownames(fa$loadings))


