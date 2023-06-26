select distinct package.customer_id, package.package_id
from package natural join ( select *
							from loading natural join shipment
                            where shipment.vehicle_id='22222224' and loading.is_visited=true
                            order by priority_order desc limit 1) as accident
