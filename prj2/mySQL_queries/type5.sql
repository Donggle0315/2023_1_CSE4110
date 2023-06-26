select customer.customer_id, customer.address, A.sumcharge
from customer natural join (select package.customer_id, sum(service.charge) as sumcharge
							from package natural join service
                            where package.actual_arrive_date>='2023-06-01' and package.actual_arrive_date<'2023-07-01'
                            group by package.customer_id) as A
