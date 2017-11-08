function a()
{
	var n, i, j, k, m, last, total;
	var  duration = [], es = [], ef = [], ls = [], lf = [], nofp = [], nofs = [];
	var activity = [], predecessor = [], successor = [];

	n = prompt("N");

	console.log(" Enter the activity names in order: ");
	for(i=0; i<n; i++)
	{
		activity[i] = prompt("Activity"+(i+1)) ;
		console.log(activity[i]);
	}

	console.log(" For each activity, enter the duration and predecessors: ");
	for(i=0; i<n; i++)
	{
		duration[i] = parseInt(prompt("Duration for activity "+activity[i]));
		nofp[i] = parseInt(prompt("Number of predecessors"));

		if(nofp[i])
		{
			predecessor[i] = []
			for(j=0; j<nofp[i]; j++)
			{
				predecessor[i][j] = prompt("predecessor for activity"+activity[i]+" "+(j+1));
			}
		}
	}

	//successors
	for(m=0; m<n; m++)
	{
		k=0;
		successor[m] = [];
		for(i=0; i<n; i++)
		{
			for(j=0; j<nofp[i]; j++)
			{
				if(predecessor[i][j]==activity[m])
				{
					successor[m][k]=activity[i];
					k++;
				}
			}
		}
		nofs[m]=k;
	}

	//earliest start & earliest finish
	for(i=0; i<n; i++)
	{
		if(nofp[i]==0)
		{
			es[i]=0;
			ef[i]=es[i]+duration[i];
		}
		else if(nofp[i]==1)
		{
			for(j=0; j<n; j++)
			{
					if(predecessor[i][0]==activity[j])
					{
						es[i]=ef[j];
						ef[i]=es[i]+duration[i];
					}
			}
		}
		else
		{
			last=-1;
			for(j=0; j<n; j++)
			{
				for(k=0; k<nofp[i]; k++)
				{
					if(predecessor[i][k]==activity[j])
					{
						if(last<ef[j])
						{
							last=ef[j];
						}
					}
				}
			}
			es[i]=last;
			ef[i]=es[i]+duration[i];
		}
	}

	total=-1;
	for(i=0; i<n; i++)
	{
		if(ef[i]>total)
			total=ef[i];
	}

	console.log("Total time taken for the production is "+total);

	//latest start & latest finish
	for(i=n-1; i>=0; i--)
	{
		if(nofs[i]==0)
		{
			lf[i]=total;
			ls[i]=lf[i]-duration[i];
		}
		else if(nofs[i]==1)
		{
			for(j=0; j<n; j++)
			{
				if(successor[i][0]==activity[j])
				{
					lf[i]=ls[j];
					ls[i]=lf[i]-duration[i];
				}
			}
		}
		else
		{
			last=1000;
			for(j=0; j<n; j++)
			{
				for(k=0; k<nofs[i]; k++)
				{
					if(successor[i][k]==activity[j])
					{
						if(last>ls[j])
						{
							last=ls[j];
						}
					}
				}
			}
			lf[i]=last;
			ls[i]=lf[i]-duration[i];
		}
		console.log("LF, LS"+activity[i]+" -> "+lf[i]+" - "+ls[i]);
	}

	console.log(" The ES, EF, LS, LF values are: ");
	console.log(" Activity - ES - EF - LS - LF");

	for(i=0; i<n; i++)
	{
		console.log(activity[i]+" - "+es[i]+" - "+ef[i]+" - "+ls[i]+" - "+lf[i]);
	}

	console.log(" The critical path is: ");
	k=0;
	for(i=0; i<n; i++)
	{
		if(ef[i]==lf[i])
			k++;
	}

	for(i=0; i<n; i++)
	{
		if(ef[i]==lf[i])
		{
			console.log(activity[i]+" --> ");
			k--;
			if(k==1)
				break;
		}
	}
	for(j=i+1; j<n; j++)
	{
		if(ef[j]==lf[j])
		{
			console.log(activity[j]);
		}
	}

}
